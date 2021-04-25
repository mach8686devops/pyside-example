/*! 
* Copyright (C) 2018 女儿叫老白
* 版权所有。
* 代码仅用于课程《Qt 5/PyQt 5实战指南》的学习，请勿传播。
* 免责声明:代码不保证稳定性，请勿用作商业用途，否则后果自负。

\file: main.cpp
\brief main()函数的实现文件
\author 女儿叫老白   微信公众号:软件特攻队(微信号:xingdianketang)
\Date 2018/9
*/

#include <QApplication>
#include <QStandardItemModel>
#include <QTreeView>
#include <QHeaderView>

#include <iostream>
#include "base/basedll/baseapi.h"

#include "qglobal.h"
#include "country.h"
#include "province.h"
#include "city.h"


CCountry* createCountry(void);

int main(int argc, char * argv[]) {
	Q_UNUSED(argc);
	Q_UNUSED(argv);

    QApplication app(argc, argv);

    // 构建模型中的数据
    CCountry* pCountry = createCountry();
    if (nullptr == pCountry){
        return 1;
    }

    // 构建变量用于指向pCountry中的数据
    QList<CProvince*> lstProvinces;
    QList<CCity*> lstCities;

    pCountry->getProvinces(lstProvinces);

    // 构建模型，并设置一些属性
    QStandardItemModel model;
    QTreeView treeView;
    treeView.setModel(&model);
    treeView.setRootIsDecorated(true); // 根分支是否可展开
    treeView.header()->setFirstSectionMovable(false);// false:首列不允许被移动,true:首列允许移动
    treeView.header()->setStretchLastSection(true); // 将最后一列设置为自动拉伸,true:自动拉伸,false:不自动拉伸。

    treeView.setWindowTitle("normal tree view");
    treeView.show();

    // 将数据添加到模型，包括子数据
    // 得到根节点
    QStandardItem* pItemRoot = model.invisibleRootItem();
    // 得到根节点的序号
    QModelIndex indexRoot = pItemRoot->index();
    // 构建country节点
    QStandardItem* pItemCountry = new QStandardItem(pCountry->getName());
    // 将country节点作为根节点的子节点
    pItemRoot->appendRow(pItemCountry);
    // 设置country的字体、字色
    QFont ft(QString::fromLocal8Bit("宋体"), 16);
    ft.setBold(true);
    pItemCountry->setData(ft, Qt::FontRole);
    pItemCountry->setData(QColor(Qt::red), Qt::TextColorRole);
    QImage image(":/images/china.png");
    pItemCountry->setData(image.scaled(QSize(24, 24)), Qt::DecorationRole);

    // 设置 pItemRoot 的列数以便显示省的个数
    const int COLUMNCOUNT = 2; // 列数
    pItemRoot->setColumnCount(COLUMNCOUNT);
    // 必须在设置列数之后才能设置标题中该列的数据。即列不存在时，设置数据无效。
    model.setHeaderData(1, Qt::Horizontal, "sub item count", Qt::DisplayRole);

    // 在Country节点所在的行的第1列显示省的个数
    model.setData(model.index(0, 1, indexRoot), lstProvinces.size());

    // 遍历并构建省、城市两级节点
    QStandardItem* pItemProvince = nullptr;
    QStandardItem* pItemCity = nullptr;
    int idProvince = 0;
    QList<CProvince*>::iterator iteProvince = lstProvinces.begin();
    QList<CCity*>::iterator iteCity;
    while (iteProvince != lstProvinces.end()) {
        // 构建省节点，并添加到国家节点的下级
        pItemProvince = new QStandardItem((*iteProvince)->getName());
        pItemCountry->appendRow(pItemProvince);

        // 设置Country的列数
        pItemCountry->setColumnCount(COLUMNCOUNT);

        (*iteProvince)->getCities(lstCities);
        // 设置Province节点的第0列的文本颜色为蓝色
        model.setData(model.index(idProvince, 0, pItemCountry->index()),
                      QColor(Qt::blue),
                      Qt::TextColorRole);

        // 设置Country节点第1列数据为城市个数
        model.setData(model.index(idProvince, 1, pItemCountry->index()),
                      lstCities.size());

        // 遍历所有城市
        iteCity = lstCities.begin();
        while (iteCity != lstCities.end()) {
            // 构建城市节点
            pItemCity = new QStandardItem((*iteCity)->getName());
            // 添加城市节点
            pItemProvince->appendRow(pItemCity);

            iteCity++;
        }

        idProvince++;

        iteProvince++;
    }

    return app.exec();
}


/**
* @brief构建CCountry对象.
* @return CCountry对象指针
*/
CCountry* createCountry(void) {
	CProvince* pProvince = NULL;
	CCity* pCity = NULL;
	CCountry* pCountry = new CCountry(QString::fromLocal8Bit("中国"));
	if (NULL == pCountry) {
		return NULL;
	}
	// add province
	{
		pProvince = new CProvince();
		pCountry->addProvince(pProvince);
		pProvince->setCountry(pCountry);
		pProvince->setName(QString::fromLocal8Bit("山东"));
		// add city
		pCity = new CCity();
		pCity->setName(QString::fromLocal8Bit("济南"));
		pCity->setProvince(pProvince);
		pProvince->addCity(pCity);

		// add city
		pCity = new CCity();
		pCity->setName(QString::fromLocal8Bit("青岛"));
		pCity->setProvince(pProvince);
		pProvince->addCity(pCity);
	}
	// add province
	{
		pProvince = new CProvince();
		pCountry->addProvince(pProvince);
		pProvince->setCountry(pCountry);
		pProvince->setName(QString::fromLocal8Bit("河北"));
		// add city
		pCity = new CCity();
        pCity->setName(QString::fromLocal8Bit("北戴河"));
		pCity->setProvince(pProvince);
		pProvince->addCity(pCity);

		// add city
		pCity = new CCity();
        pCity->setName(QString::fromLocal8Bit("张家口"));
		pCity->setProvince(pProvince);
		pProvince->addCity(pCity);

		// add city
		pCity = new CCity();
        pCity->setName(QString::fromLocal8Bit("保定"));
		pCity->setProvince(pProvince);
		pProvince->addCity(pCity);
	}

	// 返回构建的CCountry对象
	return pCountry;
	
}
