#include "GraphicSystem.h"

#include "Overlay\OgreOverlaySystem.h"
#include "Compositor\OgreCompositorManager2.h"
#include "Hlms\Unlit\OgreHlmsUnlit.h"
#include "Hlms\Pbs\OgreHlmsPbs.h"

#include <SDL2\SDL.h>
#include <SDL2\SDL_syswm.h>

GraphicSystem::GraphicSystem(Ogre::ColourValue backgroundColour) :
	m_backgroundColour(backgroundColour)
{
}

GraphicSystem::~GraphicSystem()
{
}

void GraphicSystem::setConfigPath(std::string configPath)
{
	m_configPath = configPath;
}

void GraphicSystem::setLogPath(std::string logPath)
{
	m_logPath = logPath;
}

void GraphicSystem::setResourcePath(std::string pluginPath)
{
	m_resourcePath = pluginPath;
}

bool GraphicSystem::initialize(const std::string &windowTitle)
{
	if( SDL_Init( SDL_INIT_EVERYTHING ) != 0 )
	{
		OGRE_EXCEPT( Ogre::Exception::ERR_INTERNAL_ERROR, "Cannot initialize SDL2!", "GraphicsSystem::initialize" );
	}

	m_root = OGRE_NEW Ogre::Root(m_configPath + "plugins.cfg", m_configPath + "graphic.cfg",	m_logPath + "ogre.log" );

	if( !m_root->restoreConfig() )
	{
		if( !m_root->showConfigDialog() )
		{
			return false;
		};
	};

	m_root->getRenderSystem()->setConfigOption( "sRGB Gamma Conversion", "Yes" );
	m_root->initialise(false);

	Ogre::ConfigOptionMap& cfgOpts = m_root->getRenderSystem()->getConfigOptions();

	int width   = 1280;
	int height  = 720;


	Ogre::ConfigOptionMap::iterator opt = cfgOpts.find( "Video Mode" );
	if( opt != cfgOpts.end() )
	{
		//Ignore leading space
		const Ogre::String::size_type start = opt->second.currentValue.find_first_of("012356789");
		//Get the width and height
		Ogre::String::size_type widthEnd = opt->second.currentValue.find(' ', start);
		// we know that the height starts 3 characters after the width and goes until the next space
		Ogre::String::size_type heightEnd = opt->second.currentValue.find(' ', widthEnd+3);
		// Now we can parse out the values
		width   = Ogre::StringConverter::parseInt( opt->second.currentValue.substr( 0, widthEnd ) );
		height  = Ogre::StringConverter::parseInt( opt->second.currentValue.substr(widthEnd+3, heightEnd ) );
	}

	Ogre::NameValuePairList params;
	bool fullscreen = Ogre::StringConverter::parseBool( cfgOpts["Full Screen"].currentValue );
	
	int screen = 0;
	int posX = SDL_WINDOWPOS_CENTERED_DISPLAY(screen);
	int posY = SDL_WINDOWPOS_CENTERED_DISPLAY(screen);

	if(fullscreen)
	{
		posX = SDL_WINDOWPOS_UNDEFINED_DISPLAY(screen);
		posY = SDL_WINDOWPOS_UNDEFINED_DISPLAY(screen);
	};

	m_sdlWindow = SDL_CreateWindow(windowTitle.c_str()    // window title
				, posX               // initial x position
				, posY               // initial y position
				, width              // width, in pixels
				, height             // height, in pixels
				, SDL_WINDOW_SHOWN | (fullscreen ? SDL_WINDOW_FULLSCREEN : 0) | SDL_WINDOW_RESIZABLE );

	//Get the native whnd
	SDL_SysWMinfo wmInfo;
	SDL_VERSION( &wmInfo.version );

	if( SDL_GetWindowWMInfo( m_sdlWindow, &wmInfo ) == SDL_FALSE )
	{
		OGRE_EXCEPT( Ogre::Exception::ERR_INTERNAL_ERROR, "Couldn't get WM Info! (SDL2)", "GraphicsSystem::initialize" );
	};

	Ogre::String winHandle;
	switch( wmInfo.subsystem )
	{
		case SDL_SYSWM_WINDOWS:
			// Windows code
			winHandle = Ogre::StringConverter::toString( (uintptr_t)wmInfo.info.win.window );
			break;

		default:
			OGRE_EXCEPT( Ogre::Exception::ERR_NOT_IMPLEMENTED, "Unexpected WM! (SDL2)", "GraphicsSystem::initialize" );
			break;
	};

	params.insert( std::make_pair("externalWindowHandle",  winHandle) );
	params.insert( std::make_pair("title", windowTitle) );
	params.insert( std::make_pair("gamma", "true") );
	params.insert( std::make_pair("FSAA", cfgOpts["FSAA"].currentValue) );
	params.insert( std::make_pair("vsync", cfgOpts["VSync"].currentValue) );
	
	m_renderWindow = Ogre::Root::getSingleton().createRenderWindow( windowTitle, width, height, fullscreen, &params);

	m_overlaySystem = OGRE_NEW Ogre::v1::OverlaySystem();


	setupResources();
	loadResources();

	chooseSceneManager();
	createCamera();
	m_workspace = setupCompositor();

/*
	BaseSystem::initialize();
	*/

	return true;
}

void GraphicSystem::loadResources()
{
	registerHlms();

	// Initialise, parse scripts etc
	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
}

void GraphicSystem::registerHlms()
{
	Ogre::ConfigFile cf;
	cf.load(m_resourcePath + "data.cfg");

	Ogre::String dataFolder = cf.getSetting("DoNotUseAsResource", "Hlms", "");

	if (dataFolder.empty())
		dataFolder = "./";
	else if (*(dataFolder.end() - 1) != '/')
		dataFolder += "/";

	Ogre::RenderSystem *renderSystem = m_root->getRenderSystem();
/*	Ogre::Archive *archiveUnlit = Ogre::ArchiveManager::getSingletonPtr()->load(dataFolder, "FileSystem", true);
	Ogre::ArchiveVec library;
	Ogre::HlmsUnlit *hlmsUnlit = OGRE_NEW Ogre::HlmsUnlit(archiveUnlit, &library);
	Ogre::Root::getSingleton().getHlmsManager()->registerHlms(hlmsUnlit);
	library.pop_back();
	*/

	Ogre::String shaderSyntax = "GLSL";
	if (renderSystem->getName() == "Direct3D11 Rendering Subsystem")
		shaderSyntax = "HLSL";
	else if (renderSystem->getName() == "Metal Rendering Subsystem")
		shaderSyntax = "Metal";
	
	Ogre::Archive *archiveLibrary = Ogre::ArchiveManager::getSingletonPtr()->load(dataFolder + "Hlms/Common/" + shaderSyntax, "FileSystem", true);
	Ogre::Archive *archiveLibraryAny = Ogre::ArchiveManager::getSingletonPtr()->load(dataFolder + "Hlms/Common/Any", "FileSystem", true);
	Ogre::Archive *archivePbsLibraryAny = Ogre::ArchiveManager::getSingletonPtr()->load(dataFolder + "Hlms/Pbs/Any", "FileSystem", true);
	Ogre::Archive *archiveUnlitLibraryAny = Ogre::ArchiveManager::getSingletonPtr()->load(dataFolder + "Hlms/Unlit/Any", "FileSystem", true);

	Ogre::ArchiveVec library;
	library.push_back(archiveLibrary);
	library.push_back(archiveLibraryAny);

	Ogre::Archive *archiveUnlit = Ogre::ArchiveManager::getSingletonPtr()->load(dataFolder + "Hlms/Unlit/" + shaderSyntax, "FileSystem", true);

	library.push_back(archiveUnlitLibraryAny);
	Ogre::HlmsUnlit *hlmsUnlit = OGRE_NEW Ogre::HlmsUnlit(archiveUnlit, &library);
	Ogre::Root::getSingleton().getHlmsManager()->registerHlms(hlmsUnlit);
	library.pop_back();

	Ogre::Archive *archivePbs = Ogre::ArchiveManager::getSingletonPtr()->load(dataFolder + "Hlms/Pbs/" + shaderSyntax, "FileSystem", true);
	library.push_back(archivePbsLibraryAny);
	Ogre::HlmsPbs *hlmsPbs = OGRE_NEW Ogre::HlmsPbs(archivePbs, &library);
	Ogre::Root::getSingleton().getHlmsManager()->registerHlms(hlmsPbs);
	library.pop_back();
	
	if (renderSystem->getName() == "Direct3D11 Rendering Subsystem")
	{
		//Set lower limits 512kb instead of the default 4MB per Hlms in D3D 11.0
		//and below to avoid saturating AMD's discard limit (8MB) or
		//saturate the PCIE bus in some low end machines.
		bool supportsNoOverwriteOnTextureBuffers;
		renderSystem->getCustomAttribute("MapNoOverwriteOnDynamicBufferSRV", &supportsNoOverwriteOnTextureBuffers);

		if (!supportsNoOverwriteOnTextureBuffers)
		{
			hlmsPbs->setTextureBufferDefaultSize(512 * 1024);
			hlmsUnlit->setTextureBufferDefaultSize(512 * 1024);
		}
	}
}

void GraphicSystem::addResourceLocation(const Ogre::String &archName, const Ogre::String &typeName, const Ogre::String &secName)
{
	Ogre::ResourceGroupManager::getSingleton().addResourceLocation(archName, typeName, secName);
}

void GraphicSystem::setupResources(void)
{
	// Load resource paths from config file
	Ogre::ConfigFile cf;
	cf.load(m_resourcePath + "data.cfg");

	// Go through all sections & settings in the file
	Ogre::ConfigFile::SectionIterator seci = cf.getSectionIterator();

	Ogre::String secName, typeName, archName;
	while (seci.hasMoreElements())
	{
		secName = seci.peekNextKey();
		Ogre::ConfigFile::SettingsMultiMap *settings = seci.getNext();

		if (secName != "Hlms")
		{
			Ogre::ConfigFile::SettingsMultiMap::iterator i;
			for (i = settings->begin(); i != settings->end(); ++i)
			{
				typeName = i->first;
				archName = i->second;
				addResourceLocation(archName, typeName, secName);
			}
		}
	}

	Ogre::String dataFolder = cf.getSetting("DoNotUseAsResource", "Hlms", "");

	if (dataFolder.empty())
		dataFolder = "./";
	else if (*(dataFolder.end() - 1) != '/')
		dataFolder += "/";

	addResourceLocation(dataFolder, "FileSystem", "General");
}

void GraphicSystem::deinitialize(void)
{
	m_renderWindow = nullptr;
	
	if (m_sceneManager)
		m_sceneManager->removeRenderQueueListener(m_overlaySystem);

	OGRE_DELETE m_overlaySystem;
	m_overlaySystem = nullptr;

	OGRE_DELETE m_root;
	m_root = nullptr;

	if (m_sdlWindow)
	{
		// Restore desktop resolution on exit
		SDL_SetWindowFullscreen(m_sdlWindow, 0);
		SDL_DestroyWindow(m_sdlWindow);
		m_sdlWindow = nullptr;
	}

	SDL_Quit();
}

void GraphicSystem::update()
{
	Ogre::WindowEventUtilities::messagePump();

	if (m_renderWindow->isVisible())
		m_root->renderOneFrame();

	//SDL_SetWindowPosition( mSdlWindow, 0, 0 );
	/*SDL_Rect rect;
	SDL_GetDisplayBounds( 0, &rect );
	SDL_GetDisplayBounds( 0, &rect );*/
}

void GraphicSystem::chooseSceneManager()
{
	Ogre::InstancingThreadedCullingMethod threadedCullingMethod = Ogre::INSTANCING_CULLING_SINGLETHREAD;
#if OGRE_DEBUG_MODE
	//Debugging multithreaded code is a PITA, disable it.
	const size_t numThreads = 1;
#else
	//getNumLogicalCores() may return 0 if couldn't detect
	const size_t numThreads = std::max<size_t>(1, Ogre::PlatformInformation::getNumLogicalCores());
	//See doxygen documentation regarding culling methods.
	//In some cases you may still want to use single thread.
	//if( numThreads > 1 )
	//	threadedCullingMethod = Ogre::INSTANCING_CULLING_THREADED;
#endif
	// Create the SceneManager, in this case a generic one
	m_sceneManager = m_root->createSceneManager(Ogre::ST_GENERIC, numThreads, threadedCullingMethod, "ExampleSMInstance");
	m_sceneManager->addRenderQueueListener(m_overlaySystem);

	//Set sane defaults for proper shadow mapping
	m_sceneManager->setShadowDirectionalLightExtrusionDistance(500.0f);
	m_sceneManager->setShadowFarDistance(500.0f);
}

void GraphicSystem::createCamera(void)
{
	m_camera = m_sceneManager->createCamera("Main Camera");

	m_camera->setPosition(Ogre::Vector3(0, 150, 150));
	// Look back along -Z
	m_camera->lookAt(Ogre::Vector3(0, 0, 0));
	m_camera->setNearClipDistance(0.2f);
	m_camera->setFarClipDistance(1000.0f);
	m_camera->setAutoAspectRatio(true);
}

Ogre::CompositorWorkspace* GraphicSystem::setupCompositor()
{
	Ogre::CompositorManager2 *compositorManager = m_root->getCompositorManager2();

	const Ogre::String workspaceName("MyWorkspace");
	if (!compositorManager->hasWorkspaceDefinition(workspaceName))
	{
		compositorManager->createBasicWorkspaceDef(workspaceName, m_backgroundColour, Ogre::IdString());
	}

	return compositorManager->addWorkspace(m_sceneManager, m_renderWindow, m_camera, workspaceName, true);
}