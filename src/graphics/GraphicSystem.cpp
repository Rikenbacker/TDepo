#include "GraphicSystem.h"

#include "Overlay\OgreOverlaySystem.h"

#include <SDL2\SDL.h>
#include <SDL2\SDL_syswm.h>

GraphicSystem::GraphicSystem()
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

void GraphicSystem::setPluginPath(std::string pluginPath)
{
	m_pluginPath = pluginPath;
}

bool GraphicSystem::initialize(const std::string &windowTitle)
{
	if( SDL_Init( SDL_INIT_EVERYTHING ) != 0 )
	{
		OGRE_EXCEPT( Ogre::Exception::ERR_INTERNAL_ERROR, "Cannot initialize SDL2!", "GraphicsSystem::initialize" );
	}

	m_root = OGRE_NEW Ogre::Root(m_pluginPath + "plugins.cfg", m_configPath + "graphic.cfg",	m_logPath + "ogre.log" );

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

/*
	setupResources();
	loadResources();
	chooseSceneManager();
	createCamera();
	mWorkspace = setupCompositor();

	#if OGRE_USE_SDL2
	mInputHandler = new SdlInputHandler( mSdlWindow, mCurrentGameState,
	mCurrentGameState, mCurrentGameState );
	#endif

	BaseSystem::initialize();
	*/

	return true;
}

void GraphicSystem::deinitialize(void)
{
	m_renderWindow = nullptr;
	/*
	if (mSceneManager)
		mSceneManager->removeRenderQueueListener(mOverlaySystem);

	OGRE_DELETE mOverlaySystem;
	mOverlaySystem = 0;
*/

/*
	delete mInputHandler;
	mInputHandler = 0;
*/

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