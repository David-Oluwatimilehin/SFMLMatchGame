#include "StateMachine.h"


StateMachine::StateMachine():
	m_resume{false},
	m_running{false}
{
	std::cout << "StateMachine Init\n";
}

void StateMachine::Run(std::unique_ptr<State> state)
{
	m_running = true;

	m_stateStack.push(std::move(state));
}

void StateMachine::NextState()
{
	if (m_resume)
	{
		// Cleanup the current state
		if (!m_stateStack.empty())
		{
			m_stateStack.pop();
		}

		// Resume previous state
		if (!m_stateStack.empty())
		{
			m_stateStack.top()->Resume();
		}

		m_resume = false;
	}

	// There needs to be a state
	if (!m_stateStack.empty())
	{
		auto temp = m_stateStack.top()->Next();

		// Only change states if there's a next one existing
		if (temp != nullptr)
		{
			// Replace the running state
			if (temp->isReplacing())
			{
				m_stateStack.pop();
			}
			// Pause the running state
			else
			{
				m_stateStack.top()->Pause();
			}

			m_stateStack.push(std::move(temp));
		}
	}
}

void StateMachine::LastState()
{
	m_resume = true;
}

void StateMachine::Update()
{
	m_stateStack.top()->Update();
}

void StateMachine::Draw()
{
	m_stateStack.top()->Draw();
}

void StateMachine::Quit()
{
	m_running = false;
	std::cout << "Game Stopped\n";
}