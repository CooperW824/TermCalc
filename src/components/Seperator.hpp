#ifndef SEPERATOR_HPP
#define SEPERATOR_HPP

#include "ftxui/component/component.hpp"
#include "ftxui/component/component_base.hpp"

namespace TermCalc
{
    class Seperator: public ftxui::ComponentBase
    {
        public:
            Seperator(): ComponentBase() {}
            ~Seperator() {}
            ftxui::Element Render() override
            {
                return ftxui::separator();
            }
    };
}


#endif /* SEPERATOR_HPP */
