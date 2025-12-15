#include "facility.h"
#include "ui_facility.h"
#include"phonebooklogic.h"
#include <QMessageBox>
#include <QInputDialog>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QAbstractItemView>
facility::facility(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::facility)
, m_phoneLogic(new phonebooklogic(this))
{
    ui->setupUi(this);
    this->setWindowTitle("校内电话黄历查询系统");
    this->setFixedSize(800, 600);
    if (!m_phoneLogic->initDatabase()) {
        QMessageBox::critical(this, "错误", "数据库初始化失败！");
    }
    // 初始化表格
    QStringList headers = {"部门名称", "联系人", "联系电话", "办公地址", "备注"};
    ui->tablePhoneBook->setColumnCount(headers.size());
    ui->tablePhoneBook->setHorizontalHeaderLabels(headers);
    ui->tablePhoneBook->horizontalHeader()->setStretchLastSection(true);
    ui->tablePhoneBook->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tablePhoneBook->setSelectionBehavior(QAbstractItemView::SelectRows);

    // 加载默认数据
    loadPhoneBookData(m_phoneLogic->getAllPhoneBook());
}

facility::~facility()
{
    delete ui;
}
// 加载数据到表格
void facility::loadPhoneBookData(const QList<PhoneBookInfo> &data)
{
    ui->tablePhoneBook->setRowCount(0); // 清空表格

    for (int i = 0; i < data.size(); ++i) {
        const PhoneBookInfo &info = data[i];
        ui->tablePhoneBook->insertRow(i);

        // 创建第一列的item，并绑定id数据（用Qt::UserRole存储自定义数据）
        QTableWidgetItem *deptItem = new QTableWidgetItem(info.deptName);
        deptItem->setData(Qt::UserRole, info.id); // 把id存到item的UserRole里
        ui->tablePhoneBook->setItem(i, 0, deptItem);

        // 填充其他列
        ui->tablePhoneBook->setItem(i, 1, new QTableWidgetItem(info.contactPerson));
        ui->tablePhoneBook->setItem(i, 2, new QTableWidgetItem(info.phoneNum));
        ui->tablePhoneBook->setItem(i, 3, new QTableWidgetItem(info.officeAddr));
        ui->tablePhoneBook->setItem(i, 4, new QTableWidgetItem(info.remark));
    }

    // 调整列宽
    for (int i = 0; i < ui->tablePhoneBook->columnCount() - 1; ++i) {
        ui->tablePhoneBook->resizeColumnToContents(i);
    }
}
// 搜索按钮
void facility::on_btnSearch_clicked()
{
    QString keyword = ui->leSearch->text();
    QList<PhoneBookInfo> result = m_phoneLogic->searchPhoneBook(keyword);
    loadPhoneBookData(result);

    if (result.isEmpty()) {
        QMessageBox::information(this, "提示", "未找到匹配记录！");
    }
}

// 重置按钮
void facility::on_btnReset_clicked()
{
    ui->leSearch->clear();
    loadPhoneBookData(m_phoneLogic->getAllPhoneBook());
}

// 添加按钮
void facility::on_btnAdd_clicked()
{
    PhoneBookInfo info;
    info.deptName = QInputDialog::getText(this, "添加记录", "部门名称：");
    if (info.deptName.isEmpty()) return;

    info.phoneNum = QInputDialog::getText(this, "添加记录", "联系电话：");
    if (info.phoneNum.isEmpty()) return;

    info.contactPerson = QInputDialog::getText(this, "添加记录", "联系人：");
    info.officeAddr = QInputDialog::getText(this, "添加记录", "办公地址：");
    info.remark = QInputDialog::getText(this, "添加记录", "备注：");

    QString msg;
    if (m_phoneLogic->addPhoneBook(info, msg)) {
        QMessageBox::information(this, "成功", msg);
        loadPhoneBookData(m_phoneLogic->getAllPhoneBook());
    } else {
        QMessageBox::warning(this, "失败", msg);
    }
}

// 修改按钮
void facility::on_btnEdit_clicked()
{
    int curRow = ui->tablePhoneBook->currentRow();
    if (curRow < 0) {
        QMessageBox::warning(this, "提示", "请选中要修改的记录！");
        return;
    }

    // 获取选中行第一列的item，从中读取id
    QTableWidgetItem *deptItem = ui->tablePhoneBook->item(curRow, 0);
    int id = deptItem->data(Qt::UserRole).toInt(); // 读取之前存储的id

    // 获取原有数据
    PhoneBookInfo info;
    info.id = id;
    info.deptName = ui->tablePhoneBook->item(curRow, 0)->text();
    info.contactPerson = ui->tablePhoneBook->item(curRow, 1)->text();
    info.phoneNum = ui->tablePhoneBook->item(curRow, 2)->text();
    info.officeAddr = ui->tablePhoneBook->item(curRow, 3)->text();
    info.remark = ui->tablePhoneBook->item(curRow, 4)->text();

    // 编辑数据
    info.deptName = QInputDialog::getText(this, "修改记录", "部门名称：", QLineEdit::Normal, info.deptName);
    if (info.deptName.isEmpty()) return;

    info.phoneNum = QInputDialog::getText(this, "修改记录", "联系电话：", QLineEdit::Normal, info.phoneNum);
    if (info.phoneNum.isEmpty()) return;

    info.contactPerson = QInputDialog::getText(this, "修改记录", "联系人：", QLineEdit::Normal, info.contactPerson);
    info.officeAddr = QInputDialog::getText(this, "修改记录", "办公地址：", QLineEdit::Normal, info.officeAddr);
    info.remark = QInputDialog::getText(this, "修改记录", "备注：", QLineEdit::Normal, info.remark);

    // 提交修改
    QString msg;
    if (m_phoneLogic->editPhoneBook(info, msg)) {
        QMessageBox::information(this, "成功", msg);
        loadPhoneBookData(m_phoneLogic->getAllPhoneBook());
    } else {
        QMessageBox::warning(this, "失败", msg);
    }
}

// 删除按钮
void facility::on_btnDelete_clicked()
{
    int curRow = ui->tablePhoneBook->currentRow();
    if (curRow < 0) {
        QMessageBox::warning(this, "提示", "请选中要删除的记录！");
        return;
    }

    if (QMessageBox::question(this, "确认", "是否删除该记录？") != QMessageBox::Yes) {
        return;
    }

    // 获取选中行第一列的item，读取id
    QTableWidgetItem *deptItem = ui->tablePhoneBook->item(curRow, 0);
    int id = deptItem->data(Qt::UserRole).toInt();

    // 后续删除逻辑不变...
    QString msg;
    if (m_phoneLogic->deletePhoneBook(id, msg)) {
        QMessageBox::information(this, "成功", msg);
        loadPhoneBookData(m_phoneLogic->getAllPhoneBook());
    } else {
        QMessageBox::warning(this, "失败", msg);
    }
}

