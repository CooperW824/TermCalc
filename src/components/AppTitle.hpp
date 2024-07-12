#ifndef APP_TITLE_HPP
#define APP_TITLE_HPP


#include "versioning.h"
#include "ftxui/component/component.hpp"
#include "ftxui/component/component_base.hpp"
#include "../utils.hpp"

namespace TermCalc 
{
    class AppTitle : public ftxui::ComponentBase 
    {
        public:
            AppTitle(): ComponentBase() {}
            ~AppTitle() {}
            ftxui::Element Render() override 
            {
                return ftxui::hbox({
                    ftxui::vbox({
                        ftxui::text(m_appTitle) | ftxui::bold | ftxui::center,
                        ftxui::text(padString("Copyright (c) Cooper Werner, 2024", 1)) | ftxui::center,
                        ftxui::text("MIT Licensed") | ftxui::center
                    })
                }) | ftxui::flex;
            }
        private:
            std::string m_appTitle = std::string("TermCalc ") + std::string(VERSION);
    };
};

#endif /* APP_TITLE_HPP */
