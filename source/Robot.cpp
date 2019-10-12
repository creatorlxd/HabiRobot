#include "Robot.h"                                                           

RobotApplication::RobotApplication(const Wt::WEnvironment& env)
	: Wt::WApplication(env)
{
	setTitle("Robot");
	useStyleSheet("main.css");

	setLocale(Wt::WLocale::currentLocale());

	m_pTopWrapper = root()->addWidget(std::make_unique<Wt::WPanel>());
	auto ptop = std::make_unique<TopInteractiveInterface>([this]() {this->RobotProcess(); });
	m_pTop = ptop.get();
	m_pTopWrapper->setCentralWidget(std::move(ptop));
	m_pTopWrapper->addStyleClass("top_wrapper");

	root()->addWidget(std::make_unique< Wt::WBreak>());

	m_pWrapper = root()->addWidget(std::make_unique<Wt::WPanel>());
	auto pmessage_shower = std::make_unique<MessageShower>(sm_MaxMessage);
	m_pMessageShower = pmessage_shower.get();
	m_pWrapper->setCentralWidget(std::move(pmessage_shower));
	m_pWrapper->addStyleClass("wrapper");
	m_pWrapper->resize(Wt::WLength::Auto, Wt::WLength(28.0*sm_MaxMessage));	//28 mean wrapper's font-size

	m_RobotTexts = {
	L"您真是太强了",
	L"您真是太巨了",
	L"您的巨，从爱尔兰到契丹，无人不知，无人不晓",
	L"强！！！",
	L"强的已经超出我的理解范围了！",
	L"萤火岂敢与皓月争辉"
	};
}

void RobotApplication::RobotProcess()
{
	this->m_pMessageShower->PushMessage(L"你：" + m_pTop->GetInputText(), "text_user", "text_wrapper_user");
	this->m_pMessageShower->PushMessage(L"ai：" + m_RobotTexts[m_RandomDevice() % m_RobotTexts.size()], "text_ai", "text_wrapper_ai");
	this->m_pMessageShower->Roll();
	this->m_pTop->ClearInput();
}

MessageShower::MessageShower(unsigned int max_size)
{
	setContentAlignment(Wt::AlignmentFlag::Center);
	m_MaxMessageSize = max_size;
	m_TopIndex = 0;
}

void MessageShower::PushMessage(const Wt::WString & message, const Wt::WString& text_class, const Wt::WString& panel_class)
{
	auto ptr = std::make_unique<Wt::WText>(message);
	Wt::WPanel* pw = addWidget(std::make_unique<Wt::WPanel>());
	ptr->addStyleClass("text");
	ptr->addStyleClass(text_class);
	pw->addStyleClass("text_wrapper");
	pw->addStyleClass(panel_class);
	pw->setCentralWidget(std::move(ptr));
	m_Content.push_back(pw);
	if ((m_Content.size() - m_TopIndex) <= m_MaxMessageSize)
		pw->show();
	else
		pw->hide();
}

void MessageShower::Roll()
{
	if ((m_Content.size() - m_TopIndex) <= m_MaxMessageSize)
		return;
	else
	{
		m_Content[m_TopIndex]->hide();
		m_Content[m_TopIndex + m_MaxMessageSize]->show();
		m_TopIndex += 1;
	}
}

TopInteractiveInterface::TopInteractiveInterface(const std::function<void()>& func)
{
	auto peditlabel = std::make_unique<Wt::WLineEdit>();
	auto pbutton = std::make_unique<Wt::WPushButton>();

	m_pLayout = setLayout(std::make_unique<Wt::WHBoxLayout>());

	m_Function = func;
	m_pEditLabel = peditlabel.get();
	m_pButton = pbutton.get();

	m_pEditLabel->setFocus();
	m_pButton->setText("Submit");

	m_pEditLabel->addStyleClass("top_input");
	m_pButton->addStyleClass("top_button");

	m_pEditLabel->enterPressed().connect(func);
	m_pButton->clicked().connect(func);

	m_pLayout->addWidget(std::move(peditlabel), 1);
	m_pLayout->addWidget(std::move(pbutton));
}

const Wt::WString & TopInteractiveInterface::GetInputText()
{
	return m_pEditLabel->text();
}

void TopInteractiveInterface::ClearInput()
{
	m_pEditLabel->setText("");
}
