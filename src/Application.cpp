#include "Application.hpp"

#include "MenuState.hpp"

#include <memory>

Application::Application()
: m_window{{1024, 768}, "Ludum Dare Compo #32", sf::Style::Titlebar | sf::Style::Close, sf::ContextSettings{0, 0, 8}}
{
    m_window.setVerticalSyncEnabled(true);

    m_music.openFromFile("res/music.ogg");
    m_music.setLoop(true);
}

void Application::run()
{
    // Simple state machine
    std::unique_ptr<State> state(new MenuState(m_window));

    m_music.play();

    while(state != nullptr)
    {
        state = state->run();
    }
}
