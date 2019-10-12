#pragma once
#include <Wt/WApplication.h>                      
#include <Wt/WBreak.h>                            
#include <Wt/WContainerWidget.h>                  
#include <Wt/WLineEdit.h>                         
#include <Wt/WPushButton.h>                       
#include <Wt/WText.h>                             
#include <Wt/WTextArea.h> 
#include <Wt/WPanel.h>
#include <Wt/WHBoxLayout.h>
#include <random>

class MessageShower : public Wt::WContainerWidget
{
public:
	MessageShower(unsigned int max_size);
	void PushMessage(const Wt::WString& message, const Wt::WString& text_class, const Wt::WString& panel_class);
	void Roll();
private:
	unsigned int m_MaxMessageSize;
	std::vector<Wt::WPanel*> m_Content;
	unsigned int m_TopIndex;
};

class TopInteractiveInterface : public Wt::WContainerWidget
{
public:
	TopInteractiveInterface(const std::function<void()>& func);
	const Wt::WString& GetInputText();
	void ClearInput();
private:
	Wt::WLineEdit* m_pEditLabel;
	Wt::WPushButton* m_pButton;
	Wt::WHBoxLayout* m_pLayout;
	std::function<void()> m_Function;
};

constexpr unsigned int sm_MaxMessage = 15;

class RobotApplication : public Wt::WApplication
{
public:
	RobotApplication(const Wt::WEnvironment& env);
private:
	void RobotProcess();

	TopInteractiveInterface* m_pTop;
	Wt::WPanel* m_pWrapper;
	Wt::WPanel* m_pTopWrapper;
	MessageShower* m_pMessageShower;

	std::vector<Wt::WString> m_RobotTexts;
	std::random_device m_RandomDevice;
};