#include "versioning.h"

#include <iostream>
#include <functional>

#include "ftxui/component/component.hpp"
#include "ftxui/component/screen_interactive.hpp"
#include "ftxui/dom/elements.hpp"

#include "components/AppTitle.hpp"
#include "components/Seperator.hpp"
#include "components/ResultLabel.hpp"
#include "components/ButtonPanel.hpp"


int main() {
    std::string leftHandSide;
    std::string rightHandSide;
    double result;
    std::string operation;
    std::stack<double> resMemory;

    auto buttonPanel = ftxui::Make<TermCalc::ButtonPanel>(&resMemory, &leftHandSide, &rightHandSide, &operation, &result);

    ftxui::Component layout = ftxui::Container::Vertical({
        ftxui::Make<TermCalc::AppTitle>(),
        ftxui::Make<TermCalc::Seperator>(),
        ftxui::Make<TermCalc::ResultLabel>(&resMemory, &leftHandSide, &rightHandSide, &operation, &result),
        ftxui::Make<TermCalc::Seperator>(),
        buttonPanel
    }) | ftxui::border;

    layout |= ftxui::CatchEvent([&](ftxui::Event event) {
        // Handle number keys
            if (event.is_character())
            {
                char c = event.character()[0];
                if ((c >= '0' && c <= '9') || c == '.')
                {
                    buttonPanel->onNumberClick(std::string(1, c));
                    return true;
                }
            }

            // Handle operation keys
            if (event == ftxui::Event::Character('+'))
            {
                buttonPanel->onOperationClick("+");
                return true;
            }
            if (event == ftxui::Event::Character('-'))
            {
                buttonPanel->onOperationClick("-");
                return true;
            }
            if (event == ftxui::Event::Character('*'))
            {
                buttonPanel->onOperationClick("*");
                return true;
            }
            if (event == ftxui::Event::Character('/'))
            {
                buttonPanel->onOperationClick("/");
                return true;
            }

            // Handle Enter key for equals
            if (event == ftxui::Event::Return)
            {
                buttonPanel->onEqualsClick();
                return true;
            }

            // Handle backspace key
            if (event == ftxui::Event::Backspace)
            {
                buttonPanel->handleBackspace();
                return true;
            }

            // Handle clear key (e.g., 'C')
            if (event == ftxui::Event::Character('C') || event == ftxui::Event::Character('c'))
            {
                buttonPanel->clear();
                return true;
            }
        return false;
    });

    auto screen = ftxui::ScreenInteractive::FitComponent();
    screen.Loop(layout);
}




