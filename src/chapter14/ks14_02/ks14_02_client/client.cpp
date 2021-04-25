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
#include "task.h"
#include "clientconnection.h"

CClient::CClient(QWidget* pParent) :
	QDialog(pParent),
	m_pTcpSocket(new QTcpSocket(this)),
	m_pNetworkSession(NULL),
	m_pClientConnection(new CClientConnection(m_pTcpSocket, this)) {
	setupUi();
	connectSignalAndSlots();
	initialSession();
}

CClient::~CClient() {
	m_pClientConnection->disconnect();
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

	ui.btnConnect->setDefault(true);
	ui.btnGetData->setEnabled(false);
	ui.hostCombo->setEditable(true);

	m_inStream.setDevice(m_pTcpSocket);
	m_inStream.setVersion(QDataStream::Qt_5_11);
}
void CClient::connectSignalAndSlots() {
	connect(ui.btnConnect, &QAbstractButton::clicked,
		this, &CClient::slot_connectToServer);
	connect(ui.btnSetData, &QAbstractButton::clicked,
		this, &CClient::slot_SetOneData);
    connect(ui.btnGetData, &QAbstractButton::clicked,
        this, &CClient::slot_GetOneData);
    connect(ui.btnQuit, &QAbstractButton::clicked, 
		this, &QWidget::close);
    connect(m_pTcpSocket, &QIODevice::readyRead, 
		this, &CClient::slot_readyToRead);
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

void CClient::slot_SetOneData() {
	CSetOneDataTask* pSetOneDataTask = new CSetOneDataTask();
	pSetOneDataTask->setDataId(ui.leSetDataId->text().toInt());
	pSetOneDataTask->setDataValue(ui.leSetDataValue->text().toDouble());
	m_pClientConnection->addTask(pSetOneDataTask);
	m_pClientConnection->sendDeal();
}

void CClient::slot_GetOneData() {
	CGetOneDataTask* pGetOneDataTask = new CGetOneDataTask();
	pGetOneDataTask->setDataId(ui.leGetDataId->text().toInt());
	m_pClientConnection->addTask(pGetOneDataTask);
	m_pClientConnection->sendDeal();
}

void CClient::slot_connectToServer() {
	ui.btnGetData->setEnabled(false);
	m_pTcpSocket->abort();

    m_pTcpSocket->connectToHost(ui.hostCombo->currentText(),
        ui.portLineEdit->text().toInt());
}
void CClient::slot_readyToRead() {
	ETASKTYPE taskType = CTask::parseTaskType(m_inStream);
	CTask* pTask = CTask::createTask(taskType);
	if (NULL == pTask) {
		return;
	}

	bool bOk = pTask->parseFrame(m_inStream);

	if (!bOk) {
		delete pTask;
		return;
	}

	CHelloTask* pHelloTask = NULL;
	COneDataReturnedTask* pOneDataReturnedTask = NULL;
	QString str;
	QString strInfo;
	QTime tm = QTime::currentTime();
	strInfo.sprintf("%02d:%02d:%02d:", tm.hour(), tm.minute(), tm.second());

	switch (taskType) {
	case ETASK_HELLO:
		pHelloTask = dynamic_cast<CHelloTask*>(pTask);
		if (NULL != pHelloTask) {
			str = pHelloTask->getString();
		}
		break;
	case ETASK_ONEDATARETURNED:
		str = "OneDataReturned From Server.";
		pOneDataReturnedTask = dynamic_cast<COneDataReturnedTask*>(pTask);
		if (NULL != pOneDataReturnedTask) {
			qint32 id = pOneDataReturnedTask->getDataId();
			qreal value = pOneDataReturnedTask->getDataValue();
			str = QString("%1").arg(id);
			ui.leGetDataId->setText(str);
			str = QString("%1").arg(value);
			ui.leGetDataValue->setText(str);
		}
		break;
	default:
		break;
	}

	strInfo += str;
	ui.statusLabel->setText(strInfo);
	ui.btnGetData->setEnabled(true);

	delete pTask;
}
void CClient::slot_displayError(QAbstractSocket::SocketError socketError) {
	switch (socketError) {
	case QAbstractSocket::RemoteHostClosedError:
		break;
	case QAbstractSocket::HostNotFoundError:
		QMessageBox::information(this, QString::fromLocal8Bit("客户端"), QString::fromLocal8Bit("无法连接到主机，请检查注意名称与端口号是否正确."));
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

	ui.btnConnect->setEnabled(true);
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
}