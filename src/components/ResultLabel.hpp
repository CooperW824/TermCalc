#ifndef RESULT_LABEL_HPP
#define RESULT_LABEL_HPP
#include "ftxui/component/component.hpp"
#include "ftxui/component/component_base.hpp"
#include "ftxui/dom/elements.hpp"
#include "../utils.hpp"

#include <stack>

namespace TermCalc
{
    class ResultLabel : public ftxui::ComponentBase
    {
    private:
        const std::string *m_leftHandSide;
        const std::string *m_rightHandSide;
        const double *m_result;
        const std::string *m_operation;
        const std::stack<double> *m_resMemory;

    public:
        ResultLabel(
            const std::stack<double> *resMemory,
            const std::string *leftHandSide,
            const std::string *rightHandSide,
            const std::string *operation,
            const double *result) : ComponentBase(),
                                    m_resMemory(resMemory),
                                    m_leftHandSide(leftHandSide),
                                    m_rightHandSide(rightHandSide),
                                    m_operation(operation),
                                    m_result(result){};
        ~ResultLabel(){};

        ftxui::Element Render() override
        {
            std::string equation;
            if (m_leftHandSide && !m_leftHandSide->empty())
            {
                equation += formatNumber(*m_leftHandSide) + " ";
            }

            if (m_operation && !m_operation->empty())
            {
                equation += *m_operation + " ";
            }

            if (m_rightHandSide && !m_rightHandSide->empty())
            {
                equation += formatNumber(*m_rightHandSide) + " ";
            }

            return ftxui::hbox({
                ftxui::vbox({
                    ftxui::text(padString(equation, 1)) | ftxui::align_right,
                    ftxui::hbox({
                        ftxui::text(" Mem Count: " + std::to_string(m_resMemory->size())),
                        ftxui::text(padString(formatNumber(*m_result), 1)) | ftxui::align_right | ftxui::bold | ftxui::color(ftxui::Color::BlueLight) | ftxui::flex,
                    })
                }) | ftxui::flex
            });
        }
    };

}


#endif /* RESULT_LABEL_HPP */
