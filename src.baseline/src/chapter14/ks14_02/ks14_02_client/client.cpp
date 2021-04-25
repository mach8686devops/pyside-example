/*! 
* Copyright (C) 2018 女儿叫老白
* 版权所有。
* 代码仅用于课程《Qt 5/PyQt 5实战指南》的学习，请勿传播。
* 免责声明:代码不保证稳定性，请勿用作商业用途，否则后果自负。

\file: client.cpp
\brief CClient实现文件
\author 女儿叫老白   微信公众号:软件特攻队(微信号:xingdianketang)
\Date 2019/4
*/
#include "client.h"
#include <QtWidgets>
#include <QtNetwork>

CClient::CClient(QWidget* pParent) :
	QDialog(pParent),
	m_pTcpSocket(new QTcpSocket(this)),
	m_pNetworkSession(NULL) {
	setupUi();
	connectSignalAndSlots();
	initialSession();
}

CClient::~CClient() {

}
void CClient::setupUi() {
	ui.setupUi(this);
	setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
	setWindowTitle(QGuiApplication::applicationDisplayName());

	// 查找机器名
	QString name = QHostInfo::localHostName();
	if (!name.isEmpty()) {
		ui.hostCombo->addItem(name);
		QString domain = QHostInfo::localDomainName();
		if (!domain.isEmpty())
			ui.hostCombo->addItem(name + QChar('.') + domain);
	}
	if (name != QLatin1String("localhost"))
		ui.hostCombo->addItem(QString("localhost"));

	// 查找本机ip列表
	QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();

	// 把非localhost的ip地址添加到界面
	for (int i = 0; i < ipAddressesList.size(); ++i) {
		if (!ipAddressesList.at(i).isLoopback())
			ui.hostCombo->addItem(ipAddressesList.at(i).toString());
	}

	// 把localhost地址添加到最后
	for (int i = 0; i < ipAddressesList.size(); ++i) {
		if (ipAddressesList.at(i).isLoopback())
			ui.hostCombo->addItem(ipAddressesList.at(i).toString());
	}

	// 设置有效区间
	ui.portLineEdit->setValidator(new QIntValidator(1, 65535, this));
	ui.portLineEdit->setFocus();

	// 把文本标签的快捷键关联到对应的控件(主机、端口号)
	ui.hostLabel->setBuddy(ui.hostCombo);
	ui.portLabel->setBuddy(ui.portLineEdit);

	ui.btnGetData->setDefault(true);
	ui.btnGetData->setEnabled(false);
	ui.hostCombo->setEditable(true);

	m_inStream.setDevice(m_pTcpSocket);
	m_inStream.setVersion(QDataStream::Qt_5_11);
}
void CClient::connectSignalAndSlots() {
    connect(ui.hostCombo, &QComboBox::editTextChanged,
        this, &CClient::enableGetDataButton);
    connect(ui.portLineEdit, &QLineEdit::textChanged,
        this, &CClient::enableGetDataButton);
    connect(ui.btnGetData, &QAbstractButton::clicked,
        this, &CClient::slot_connectToServer);
    connect(ui.btnQuit, &QAbstractButton::clicked, this, &QWidget::close);

    connect(m_pTcpSocket, &QIODevice::readyRead, this, &CClient::slot_readyToRead);

    connect(m_pTcpSocket, QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::error),
        this, &CClient::slot_displayError);

}
void CClient::initialSession() {
	QNetworkConfigurationManager manager;
	if (manager.capabilities() & QNetworkConfigurationManager::NetworkSessionRequired) {
		// 获取网络配置
		QSettings settings(QSettings::UserScope, QLatin1String("QtProject"));
		settings.beginGroup(QLatin1String("QtNetwork"));
		const QString id = settings.value(QLatin1String("DefaultNetworkConfiguration")).toString();
		settings.endGroup();

		// 如果没有保存过网络配置，就用系统默认值
		QNetworkConfiguration config = manager.configurationFromIdentifier(id);
		if ((config.state() & QNetworkConfiguration::Discovered) !=
			QNetworkConfiguration::Discovered) {
			config = manager.defaultConfiguration();
		}

		m_pNetworkSession = new QNetworkSession(config, this);
		connect(m_pNetworkSession, &QNetworkSession::opened, this, &CClient::slot_sessionOpened);

		ui.btnGetData->setEnabled(false);
		ui.statusLabel->setText(tr("Opening network session."));
		m_pNetworkSession->open();
	}
}

void CClient::slot_connectToServer() {
	ui.btnGetData->setEnabled(false);
	m_pTcpSocket->abort();

	quint16 u16Port = static_cast<quint16>(ui.portLineEdit->text().toInt());
	m_pTcpSocket->connectToHost(ui.hostCombo->currentText(), u16Port);
}
void CClient::slot_readyToRead() {
	m_inStream.startTransaction();

	QTime tm;
	QString str;
	m_inStream >> tm;
	m_inStream >> str;

	if (!m_inStream.commitTransaction())
		return;

	QString strInfo;
	strInfo.sprintf("%02d:%02d:", tm.minute(), tm.second());
	strInfo += str;
	ui.statusLabel->setText(strInfo);
	ui.btnGetData->setEnabled(true);
}
void CClient::slot_displayError(QAbstractSocket::SocketError socketError) {
	switch (socketError) {
	case QAbstractSocket::RemoteHostClosedError:
		break;
	case QAbstractSocket::HostNotFoundError:
		//    QMessageBox::information(this, QString::fromLocal8Bit("客户端"), QString::fromLocal8Bit("无法连接到主机，请检查注意名称与端口号是否正确."));
		QMessageBox::information(this, QString::fromLocal8Bit("客户端"), QString::fromLocal8Bit(""));
		break;
	case QAbstractSocket::ConnectionRefusedError:
		QMessageBox::information(this, QString::fromLocal8Bit("客户端"),
			QString::fromLocal8Bit("连接被对方关闭。请确认服务端处于运行状态并检查服务器名称、端口号。"));
		break;
	default:
		QMessageBox::information(this, QString::fromLocal8Bit("客户端"),
			QString::fromLocal8Bit("运行出错。错误信息:%1.")
			.arg(m_pTcpSocket->errorString()));
		break;
	}

	ui.btnGetData->setEnabled(true);
}

void CClient::enableGetDataButton() {
	ui.btnGetData->setEnabled((!m_pNetworkSession || m_pNetworkSession->isOpen()) &&
		!ui.hostCombo->currentText().isEmpty() &&
		!ui.portLineEdit->text().isEmpty());

}

void CClient::slot_sessionOpened() {
	// 保存网络配置
	QNetworkConfiguration config = m_pNetworkSession->configuration();
	QString id;
	if (config.type() == QNetworkConfiguration::UserChoice) {
		id = m_pNetworkSession->sessionProperty(QLatin1String("UserChoiceConfiguration")).toString();
	}
	else {
		id = config.identifier();
	}
	QSettings settings(QSettings::UserScope, QLatin1String("QtProject"));
	settings.beginGroup(QLatin1String("QtNetwork"));
	settings.setValue(QLatin1String("DefaultNetworkConfiguration"), id);
	settings.endGroup();

	ui.statusLabel->setText(QString::fromLocal8Bit("The Server Needs to be run."));

	enableGetDataButton();
}