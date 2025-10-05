#include "Window.h"

Window::Window()
{
	m_screenHeight = 1800; // double
	m_screenWidth = 2700; // double
}

Window::~Window()
{
}

bool Window::init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if (!SDL_Init(SDL_INIT_VIDEO))
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Set texture filtering to linear --> now need to set for each texture in sdl3
		//if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		//{
		//	printf("Warning: Linear texture filtering not enabled!");
		//}

		//Create window
		m_Window = SDL_CreateWindow("Hangman", m_screenWidth, m_screenHeight, /*SDL_WINDOW_RESIZABLE |*/ SDL_WINDOW_HIGH_PIXEL_DENSITY); // we don't want a zoomed out window
		// make sure to still set the position
		SDL_SetWindowPosition(m_Window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
		if (m_Window == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Create renderer for window
			m_Renderer = SDL_CreateRenderer(m_Window, NULL);
			//SDL_SetRenderLogicalPresentation(m_Renderer, m_screenWidth, m_screenHeight, SDL_LOGICAL_PRESENTATION_LETTERBOX);
			//SDL_SetRenderLogicalPresentation(m_Renderer, m_screenWidth, m_screenHeight, SDL_LOGICAL_PRESENTATION_DISABLED);
			SDL_SetWindowSize(m_Window, m_screenWidth, m_screenHeight);
			SDL_SyncWindow(m_Window);


			if (m_Renderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor(m_Renderer, 0xFF, 0xFF, 0xFF, 0xFF);
			}
		}
	}

	return success;
}

void Window::close()
{
	//Destroy window	
	//SDL_DestroyRenderer(m_Renderer); This should be done by the renderer
	SDL_DestroyWindow(m_Window);
	m_Window = NULL;
	m_Renderer = NULL;

	//Quit SDL subsystems
	//IMG_Quit();
	SDL_Quit();
}

int Window::getScreenHeight()
{
	return m_screenHeight;
}

int Window::getScreenWidth()
{
	return m_screenWidth;
}

SDL_Window* Window::GetWindow()
{
	return m_Window;
}

SDL_Renderer* Window::GetRenderer()
{
	return m_Renderer;
}

bool Window::checkPollEvents()
{
	return (SDL_PollEvent(&m_sdlEvent) != 0);
}

bool Window::isPollEventQuit() const
{
	return (m_sdlEvent.type == SDL_EVENT_QUIT);
}

bool Window::isKeydownEventTrue() const
{
	if (m_sdlEvent.type == SDL_EVENT_KEY_DOWN)
		return true;
	if (m_sdlEvent.type == SDL_EVENT_MOUSE_BUTTON_DOWN)
		return true;
	if (m_sdlEvent.type == SDL_EVENT_TEXT_INPUT)
		return true;
	return false;
	//return (m_sdlEvent.type == SDL_EVENT_KEY_DOWN);
}

int Window::getKeyDownType() const
{
	switch (m_sdlEvent.key.key)
	{
	case SDLK_Q:
		return keydown::Q;
	case SDLK_W:
		return keydown::W;
	case SDLK_E:
		return keydown::E;
	case SDLK_R:
		return keydown::R;
	case SDLK_T:
		return keydown::T;
	case SDLK_Y:
		return keydown::Y;
	case SDLK_U:
		return keydown::U;
	case SDLK_I:
		return keydown::I;
	case SDLK_O:
		return keydown::O;
	case SDLK_P:
		return keydown::P;
	case SDLK_A:
		return keydown::A;
	case SDLK_S:
		return keydown::S;
	case SDLK_D:
		return keydown::D;
	case SDLK_F:
		return keydown::F;
	case SDLK_G:
		return keydown::G;
	case SDLK_H:
		return keydown::H;
	case SDLK_J:
		return keydown::J;
	case SDLK_K:
		return keydown::K;
	case SDLK_L:
		return keydown::L;
	case SDLK_Z:
		return keydown::Z;
	case SDLK_X:
		return keydown::X;
	case SDLK_C:
		return keydown::C;
	case SDLK_V:
		return keydown::V;
	case SDLK_B:
		return keydown::B;
	case SDLK_N:
		return keydown::N;
	case SDLK_M:
		return keydown::M;
	case SDLK_RETURN:
		return keydown::ENTER;
	case SDLK_KP_ENTER:
		return keydown::ENTER;
	case SDLK_BACKSPACE:
		return keydown::BACKSPACE;
	//default:
		//return -1;
	}
	switch (m_sdlEvent.type)
	{
	case SDL_EVENT_MOUSE_BUTTON_DOWN:
		return keydown::MOUSEDOWN;
	case SDL_EVENT_TEXT_INPUT:
		return keydown::TEXT_INPUT;
	}

	// default
	return -1;
}

std::string Window::getTextInputText()
{
	return m_sdlEvent.text.text;
}

void Window::getMouseCoors(float& x, float& y)
{
	SDL_GetMouseState(&x, &y);
}
