#ifndef BUTTON_PANEL_HPP
#define BUTTON_PANEL_HPP

#include "ftxui/component/component.hpp"
#include "ftxui/component/component_base.hpp"
#include "ftxui/dom/elements.hpp"

#include <string>
#include <unordered_map>
#include <functional>
#include <stdexcept>
#include <stack>

namespace TermCalc
{
    class ButtonPanel : public ftxui::ComponentBase
    {
    private:
        std::string *m_leftHandSide;
        std::string *m_rightHandSide;
        double *m_result;
        std::string *m_operation;
        std::unordered_map<std::string, std::function<double(double, double)>> m_operations;
        ftxui::Component m_ui;
        std::stack<double> *m_resMemory;
        std::chrono::steady_clock::time_point last_event_time_;
        const std::chrono::milliseconds debounce_duration_{75};

    public:
        ButtonPanel(
            std::stack<double> *resMemory,
            std::string *leftHandSide,
            std::string *rightHandSide,
            std::string *operation,
            double *result) : ComponentBase(),
                              m_resMemory(resMemory),
                              m_leftHandSide(leftHandSide),
                              m_rightHandSide(rightHandSide),
                              m_result(result),
                              m_operation(operation)
        {
            m_operations["+"] = [](double a, double b)
            { return a + b; };
            m_operations["-"] = [](double a, double b)
            { return a - b; };
            m_operations["*"] = [](double a, double b)
            { return a * b; };
            m_operations["/"] = [](double a, double b)
            { return a / b; };

            m_ui = ftxui::Container::Vertical({
                ftxui::Container::Horizontal({
                    ftxui::Button("M+", [&]
                                  { this->onResultPush(); }) |
                        ftxui::flex,
                    ftxui::Button("M-", [&]
                                  { this->onMemoryPop(); }) |
                        ftxui::flex,
                    ftxui::Button("CE", [&]
                                  { 
                                    *m_leftHandSide = ""; *m_rightHandSide = ""; *m_operation = ""; }) |
                        ftxui::flex,
                    ftxui::Button("C ", [&]
                                  { 
                                    this->clear(); }) |
                        ftxui::flex,

                }),
                ftxui::Container::Horizontal({
                    ftxui::Button("7", [&]
                                  { this->onNumberClick("7"); }) |
                        ftxui::flex,
                    ftxui::Button("8", [&]
                                  { this->onNumberClick("8"); }) |
                        ftxui::flex,
                    ftxui::Button("9", [&]
                                  { this->onNumberClick("9"); }) |
                        ftxui::flex,
                    ftxui::Button("+", [&]
                                  { this->onOperationClick("+"); }) |
                        ftxui::flex,

                }),
                ftxui::Container::Horizontal({
                    ftxui::Button("4", [&]
                                  { this->onNumberClick("4"); }) |
                        ftxui::flex,
                    ftxui::Button("5", [&]
                                  { this->onNumberClick("5"); }) |
                        ftxui::flex,
                    ftxui::Button("6", [&]
                                  { this->onNumberClick("6"); }) |
                        ftxui::flex,
                    ftxui::Button("-", [&]
                                  { this->onOperationClick("-"); }) |
                        ftxui::flex,

                }),
                ftxui::Container::Horizontal({
                    ftxui::Button("1", [&]
                                  { this->onNumberClick("1"); }) |
                        ftxui::flex,
                    ftxui::Button("2", [&]
                                  { this->onNumberClick("2"); }) |
                        ftxui::flex,
                    ftxui::Button("3", [&]
                                  { this->onNumberClick("3"); }) |
                        ftxui::flex,
                    ftxui::Button("*", [&]
                                  { this->onOperationClick("*"); }) |
                        ftxui::flex,

                }),
                ftxui::Container::Horizontal({
                    ftxui::Button("0", [&]
                                  { this->onNumberClick("0"); }) |
                        ftxui::flex,
                    ftxui::Button(".", [&]
                                  { this->onNumberClick("."); }) |
                        ftxui::flex,
                    ftxui::Button("=", [&]
                                  { this->onEqualsClick(); }) |
                        ftxui::flex,
                    ftxui::Button("/", [&]
                                  { this->onOperationClick("/"); }) |
                        ftxui::flex,
                }),
            });
        };

        ~ButtonPanel(){};

        ftxui::Element Render() override
        {
            return ftxui::vbox({m_ui->Render()});
        }

        bool OnEvent(ftxui::Event event) override
        {


            auto now = std::chrono::steady_clock::now();
            if (now - last_event_time_ < debounce_duration_)
            {
                return false;
            }
            last_event_time_ = now;

            return m_ui->OnEvent(event);
        }

        void handleBackspace()
        {
            if (m_operation->empty())
            {
                if (!m_leftHandSide->empty())
                {
                    m_leftHandSide->pop_back();
                }
            }
            else
            {
                if (!m_rightHandSide->empty())
                {
                    m_rightHandSide->pop_back();
                }else{
                    *m_operation = "";
                }
            }
        }

        void clear()
        {
            *m_leftHandSide = "";
            *m_rightHandSide = "";
            *m_operation = "";
            *m_result = 0.0;
        }

        void onResultPush()
        {
            m_resMemory->push(*m_result);
        }

        void onMemoryPop()
        {
            double popped;
            if (m_resMemory->empty())
            {
                popped = 0.0;
            }
            else
            {
                popped = m_resMemory->top();
                m_resMemory->pop();
            }

            if (*m_operation == "")
            {
                *m_leftHandSide = std::to_string(popped);
            }
            else
            {
                *m_rightHandSide = std::to_string(popped);
            }
        }

        void onNumberClick(const std::string &number)
        {
            if (m_operation->empty())
            {
                if (number == "." && m_leftHandSide->find(".") != std::string::npos)
                    return;

                *m_leftHandSide += number;
                return;
            }

            if (number == "." && m_rightHandSide->find(".") != std::string::npos)
                return;

            *m_rightHandSide += number;
        }

        void onOperationClick(const std::string &operation)
        {
            if (m_leftHandSide->empty())
            {
                if (operation == "-")
                    *m_leftHandSide += "-";

                *m_leftHandSide = std::to_string(*m_result);
            }

            if (!m_rightHandSide->empty())
            {
                this->onEqualsClick();
                *m_leftHandSide = std::to_string(*m_result);
            }

            *m_operation = operation;
        }

        void onEqualsClick()
        {
            if (m_leftHandSide->empty())
            {
                *m_result = 0.0;
                return;
            }

            if (m_rightHandSide->empty())
            {
                *m_result = std::stod(*m_leftHandSide);
                *m_leftHandSide = "";
                *m_operation = "";
                return;
            }

            double left = std::stod(*m_leftHandSide);
            double right = std::stod(*m_rightHandSide);

            *m_result = m_operations[*m_operation](left, right);
            *m_leftHandSide = "";
            *m_rightHandSide = "";
            *m_operation = "";
        }
    };
}

#endif /* BUTTON_PANEL_HPP */
