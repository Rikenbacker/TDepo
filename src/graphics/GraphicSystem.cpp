#include "GraphicSystem.h"
#include "Ogre.h"

GraphicSystem::GraphicSystem()
{
}

GraphicSystem::~GraphicSystem()
{
}

void GraphicSystem::initialize()
{
	/*
	#if OGRE_USE_SDL2
	if( SDL_Init( SDL_INIT_EVERYTHING ) != 0 )
	{
	OGRE_EXCEPT( Ogre::Exception::ERR_INTERNAL_ERROR, "Cannot initialize SDL2!",
	"GraphicsSystem::initialize" );
	}
	#endif

	Ogre::String pluginsPath;
	// only use plugins.cfg if not static
	#ifndef OGRE_STATIC_LIB
	#if OGRE_DEBUG_MODE
	pluginsPath = mPluginsPath + "plugins_d.cfg";
	#else
	pluginsPath = mPluginsPath + "plugins.cfg";
	#endif
	#endif

	mRoot = OGRE_NEW Ogre::Root( pluginsPath,
	mWriteAccessFolder + "ogre.cfg",
	mWriteAccessFolder + "Ogre.log" );

	#if OGRE_PLATFORM == OGRE_PLATFORM_APPLE || OGRE_PLATFORM == OGRE_PLATFORM_APPLE_IOS
	mResourcePath = Ogre::macBundlePath() + '/';
	#endif

	mStaticPluginLoader.install( mRoot );

	if( mAlwaysAskForConfig || !mRoot->restoreConfig() )
	{
	if( !mRoot->showConfigDialog() )
	{
	mQuit = true;
	return;
	}
	}

	#if OGRE_PLATFORM == OGRE_PLATFORM_APPLE_IOS
	{
	Ogre::RenderSystem *renderSystem =
	mRoot->getRenderSystemByName( "Metal Rendering Subsystem" );
	mRoot->setRenderSystem( renderSystem );
	}
	#endif

	mRoot->getRenderSystem()->setConfigOption( "sRGB Gamma Conversion", "Yes" );
	mRoot->initialise(false);

	Ogre::ConfigOptionMap& cfgOpts = mRoot->getRenderSystem()->getConfigOptions();

	int width   = 1280;
	int height  = 720;

	#if OGRE_PLATFORM == OGRE_PLATFORM_APPLE_IOS
	{
	Ogre::Vector2 screenRes = iOSUtils::getScreenResolutionInPoints();
	width = static_cast<int>( screenRes.x );
	height = static_cast<int>( screenRes.y );
	}
	#endif

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
	height  = Ogre::StringConverter::parseInt( opt->second.currentValue.substr(
	widthEnd+3, heightEnd ) );
	}

	Ogre::NameValuePairList params;
	bool fullscreen = Ogre::StringConverter::parseBool( cfgOpts["Full Screen"].currentValue );
	#if OGRE_USE_SDL2
	int screen = 0;
	int posX = SDL_WINDOWPOS_CENTERED_DISPLAY(screen);
	int posY = SDL_WINDOWPOS_CENTERED_DISPLAY(screen);

	if(fullscreen)
	{
	posX = SDL_WINDOWPOS_UNDEFINED_DISPLAY(screen);
	posY = SDL_WINDOWPOS_UNDEFINED_DISPLAY(screen);
	}

	mSdlWindow = SDL_CreateWindow(
	windowTitle.c_str(),    // window title
	posX,               // initial x position
	posY,               // initial y position
	width,              // width, in pixels
	height,             // height, in pixels
	SDL_WINDOW_SHOWN
	| (fullscreen ? SDL_WINDOW_FULLSCREEN : 0) | SDL_WINDOW_RESIZABLE );

	//Get the native whnd
	SDL_SysWMinfo wmInfo;
	SDL_VERSION( &wmInfo.version );

	if( SDL_GetWindowWMInfo( mSdlWindow, &wmInfo ) == SDL_FALSE )
	{
	OGRE_EXCEPT( Ogre::Exception::ERR_INTERNAL_ERROR,
	"Couldn't get WM Info! (SDL2)",
	"GraphicsSystem::initialize" );
	}

	Ogre::String winHandle;
	switch( wmInfo.subsystem )
	{
	#ifdef WIN32
	case SDL_SYSWM_WINDOWS:
	// Windows code
	winHandle = Ogre::StringConverter::toString( (uintptr_t)wmInfo.info.win.window );
	break;
	#elif __MACOSX__
	case SDL_SYSWM_COCOA:
	//required to make OGRE play nice with our window
	params.insert( std::make_pair("macAPI", "cocoa") );
	params.insert( std::make_pair("macAPICocoaUseNSView", "true") );

	winHandle  = Ogre::StringConverter::toString(WindowContentViewHandle(wmInfo));
	break;
	#else
	case SDL_SYSWM_X11:
	winHandle = Ogre::StringConverter::toString( (uintptr_t)wmInfo.info.x11.window );
	break;
	#endif
	default:
	OGRE_EXCEPT( Ogre::Exception::ERR_NOT_IMPLEMENTED,
	"Unexpected WM! (SDL2)",
	"GraphicsSystem::initialize" );
	break;
	}

	#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
	params.insert( std::make_pair("externalWindowHandle",  winHandle) );
	#else
	params.insert( std::make_pair("parentWindowHandle",  winHandle) );
	#endif
	#endif

	params.insert( std::make_pair("title", windowTitle) );
	params.insert( std::make_pair("gamma", "true") );
	params.insert( std::make_pair("FSAA", cfgOpts["FSAA"].currentValue) );
	params.insert( std::make_pair("vsync", cfgOpts["VSync"].currentValue) );

	mRenderWindow = Ogre::Root::getSingleton().createRenderWindow( windowTitle, width, height,
	fullscreen, &params );

	mOverlaySystem = OGRE_NEW Ogre::v1::OverlaySystem();

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

}