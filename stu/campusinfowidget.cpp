#include "campusinfowidget.h"
#include "ui_campusinfowidget.h"

CampusInfoWidget::CampusInfoWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CampusInfoWidget)
{
    ui->setupUi(this);
    // 初始化UI
    ui->rbtnImportant->setChecked(true);
    ui->rbtnRecruitment->setChecked(true);
    ui->lblSignUpStatus->setText("未报名");
    ui->lblSignUpStatus->setStyleSheet("color: red;");
    ui->cbxDept->addItems({"计算机学院", "文学院", "理学院", "工学院", "商学院"});

    // 初始化数据文件路径（保存在用户文档目录，避免权限问题）
    m_dataFilePath = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation)
                     + "/CampusInfoData.json";
    // 初始化文件并加载历史数据
    initDataFile();
    loadAllData();
}

CampusInfoWidget::~CampusInfoWidget()
{
    delete ui;
}
// ---------------------- 数据持久化核心方法 ----------------------
// 初始化数据文件（文件不存在则创建空JSON结构）
void CampusInfoWidget::initDataFile()
{
    QFile file(m_dataFilePath);
    if (!file.exists()) {
        // 创建空的JSON结构，包含5个模块的数组
        QJsonObject rootObj;
        rootObj["campusNews"] = QJsonArray();
        rootObj["deptNews"] = QJsonArray();
        rootObj["notice"] = QJsonArray();
        rootObj["lecture"] = QJsonArray();
        rootObj["employment"] = QJsonArray();

        QJsonDocument doc(rootObj);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            file.write(doc.toJson(QJsonDocument::Indented));
            file.close();
        } else {
            QMessageBox::warning(this, "初始化失败", "无法创建数据文件：" + file.errorString());
        }
    }
}

// 从文件加载指定类型的信息
QJsonArray CampusInfoWidget::loadInfoFromFile(InfoType type)
{
    QFile file(m_dataFilePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "加载失败", "无法读取数据文件：" + file.errorString());
        return QJsonArray();
    }

    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    file.close();
    if (!doc.isObject()) {
        QMessageBox::warning(this, "数据错误", "数据文件格式异常");
        return QJsonArray();
    }

    QJsonObject rootObj = doc.object();
    switch (type) {
    case CampusNewsType: return rootObj["campusNews"].toArray();
    case DeptNewsType: return rootObj["deptNews"].toArray();
    case NoticeType: return rootObj["notice"].toArray();
    case LectureType: return rootObj["lecture"].toArray();
    case EmploymentType: return rootObj["employment"].toArray();
    default: return QJsonArray();
    }
}

// 保存单条信息到文件
void CampusInfoWidget::saveInfoToFile(InfoType type, const QString &info)
{
    QFile file(m_dataFilePath);
    if (!file.open(QIODevice::ReadWrite | QIODevice::Text)) {
        QMessageBox::warning(this, "保存失败", "无法写入数据文件：" + file.errorString());
        return;
    }

    // 读取原有数据
    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    QJsonObject rootObj = doc.object();
    QJsonArray infoArray;

    // 获取对应类型的数组
    switch (type) {
    case CampusNewsType: infoArray = rootObj["campusNews"].toArray(); break;
    case DeptNewsType: infoArray = rootObj["deptNews"].toArray(); break;
    case NoticeType: infoArray = rootObj["notice"].toArray(); break;
    case LectureType: infoArray = rootObj["lecture"].toArray(); break;
    case EmploymentType: infoArray = rootObj["employment"].toArray(); break;
    }

    // 添加新信息
    infoArray.append(info);
    // 更新回根对象
    switch (type) {
    case CampusNewsType: rootObj["campusNews"] = infoArray; break;
    case DeptNewsType: rootObj["deptNews"] = infoArray; break;
    case NoticeType: rootObj["notice"] = infoArray; break;
    case LectureType: rootObj["lecture"] = infoArray; break;
    case EmploymentType: rootObj["employment"] = infoArray; break;
    }

    // 写入文件
    file.resize(0); // 清空原有内容
    doc.setObject(rootObj);
    file.write(doc.toJson(QJsonDocument::Indented));
    file.close();
}

// 从文件删除指定信息
void CampusInfoWidget::deleteInfoFromFile(InfoType type, const QString &info)
{
    QFile file(m_dataFilePath);
    if (!file.open(QIODevice::ReadWrite | QIODevice::Text)) {
        QMessageBox::warning(this, "删除失败", "无法修改数据文件：" + file.errorString());
        return;
    }

    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    QJsonObject rootObj = doc.object();
    QJsonArray infoArray;

    switch (type) {
    case CampusNewsType: infoArray = rootObj["campusNews"].toArray(); break;
    case DeptNewsType: infoArray = rootObj["deptNews"].toArray(); break;
    case NoticeType: infoArray = rootObj["notice"].toArray(); break;
    case LectureType: infoArray = rootObj["lecture"].toArray(); break;
    case EmploymentType: infoArray = rootObj["employment"].toArray(); break;
    }

    // 遍历删除匹配的信息
    for (int i = 0; i < infoArray.size(); ++i) {
        if (infoArray[i].toString() == info) {
            infoArray.removeAt(i);
            break;
        }
    }

    // 更新回根对象
    switch (type) {
    case CampusNewsType: rootObj["campusNews"] = infoArray; break;
    case DeptNewsType: rootObj["deptNews"] = infoArray; break;
    case NoticeType: rootObj["notice"] = infoArray; break;
    case LectureType: rootObj["lecture"] = infoArray; break;
    case EmploymentType: rootObj["employment"] = infoArray; break;
    }

    // 重新写入文件
    file.resize(0);
    doc.setObject(rootObj);
    file.write(doc.toJson(QJsonDocument::Indented));
    file.close();
}

// 程序启动时加载所有历史数据到列表
void CampusInfoWidget::loadAllData()
{
    // 1. 加载校园要闻
    QJsonArray campusNewsArray = loadInfoFromFile(CampusNewsType);
    for (const QJsonValue &val : campusNewsArray) {
        QString info = val.toString();
        QListWidgetItem *item = new QListWidgetItem(info);
        item->setToolTip(info.split("\n").mid(1).join("\n"));
        ui->lwCampusNewsList->addItem(item);
    }

    // 2. 加载院系动态
    QJsonArray deptNewsArray = loadInfoFromFile(DeptNewsType);
    for (const QJsonValue &val : deptNewsArray) {
        QString info = val.toString();
        QListWidgetItem *item = new QListWidgetItem(info);
        item->setToolTip(info.split("\n").mid(1).join("\n"));
        ui->lwDeptNewsList->addItem(item);
    }

    // 3. 加载通知公告（保留颜色标记）
    QJsonArray noticeArray = loadInfoFromFile(NoticeType);
    for (const QJsonValue &val : noticeArray) {
        QString info = val.toString();
        QListWidgetItem *item = new QListWidgetItem(info);
        item->setToolTip(info.split("\n").mid(1).join("\n"));
        // 恢复颜色：重要事项红，政策变更蓝
        if (info.contains("[重要事项]")) {
            item->setForeground(Qt::red);
        } else if (info.contains("[政策变更]")) {
            item->setForeground(Qt::blue);
        }
        ui->lwNoticeList->addItem(item);
    }

    // 4. 加载学术讲座
    QJsonArray lectureArray = loadInfoFromFile(LectureType);
    for (const QJsonValue &val : lectureArray) {
        QString info = val.toString();
        QListWidgetItem *item = new QListWidgetItem(info);
        item->setToolTip(info.split("\n").mid(3).join("\n"));
        ui->lwLectureList->addItem(item);
    }

    // 5. 加载就业信息
    QJsonArray employmentArray = loadInfoFromFile(EmploymentType);
    for (const QJsonValue &val : employmentArray) {
        QString info = val.toString();
        QListWidgetItem *item = new QListWidgetItem(info);
        item->setToolTip(info.split("\n").mid(1).join("\n"));
        ui->lwEmploymentList->addItem(item);
    }
}

// ---------------------- 右键菜单（删除功能） ----------------------
void CampusInfoWidget::contextMenuEvent(QContextMenuEvent *event)
{
    // 判断哪个列表被右键点击
    QListWidget *targetList = nullptr;
    InfoType infoType;

    if (ui->lwCampusNewsList->underMouse()) {
        targetList = ui->lwCampusNewsList;
        infoType = CampusNewsType;
    } else if (ui->lwDeptNewsList->underMouse()) {
        targetList = ui->lwDeptNewsList;
        infoType = DeptNewsType;
    } else if (ui->lwNoticeList->underMouse()) {
        targetList = ui->lwNoticeList;
        infoType = NoticeType;
    } else if (ui->lwLectureList->underMouse()) {
        targetList = ui->lwLectureList;
        infoType = LectureType;
    } else if (ui->lwEmploymentList->underMouse()) {
        targetList = ui->lwEmploymentList;
        infoType = EmploymentType;
    } else {
        // 未点击任何列表，不显示菜单
        return;
    }

    // 获取选中的项
    QListWidgetItem *selectedItem = targetList->currentItem();
    if (!selectedItem) {
        return;
    }

    // 创建右键菜单
    QMenu menu(this);
    QAction *deleteAction = new QAction("删除该条信息", this);
    connect(deleteAction, &QAction::triggered, this, [=]() {
        // 确认删除
        if (QMessageBox::question(this, "确认删除", "是否确定删除该条信息？") != QMessageBox::Yes) {
            return;
        }
        // 从列表删除
        QString info = selectedItem->text();
        delete targetList->takeItem(targetList->row(selectedItem));
        // 从文件删除
        deleteInfoFromFile(infoType, info);
    });

    menu.addAction(deleteAction);
    menu.exec(event->globalPos());
}

// ---------------------- 原有功能（新增保存逻辑） ----------------------
void CampusInfoWidget::on_btnAddCampusNews_clicked()
{
    QString title = ui->leCampusNewsTitle->text().trimmed();
    QString content = ui->teCampusNewsContent->toPlainText().trimmed();

    if (title.isEmpty() || content.isEmpty()) {
        QMessageBox::warning(this, "输入错误", "标题和内容不能为空！");
        return;
    }

    QString newsInfo = QString("[校园要闻] %1\n%2").arg(title).arg(content);
    QListWidgetItem *item = new QListWidgetItem(newsInfo);
    item->setToolTip(content);
    ui->lwCampusNewsList->addItem(item);

    // 新增：保存到文件
    saveInfoToFile(CampusNewsType, newsInfo);

    ui->leCampusNewsTitle->clear();
    ui->teCampusNewsContent->clear();
    QMessageBox::information(this, "发布成功", "校园要闻已发布！");
}

void CampusInfoWidget::on_btnAddDeptNews_clicked()
{
    QString dept = ui->cbxDept->currentText();
    QString title = ui->leDeptNewsTitle->text().trimmed();
    QString content = ui->teDeptNewsContent->toPlainText().trimmed();

    if (title.isEmpty() || content.isEmpty()) {
        QMessageBox::warning(this, "输入错误", "标题和内容不能为空！");
        return;
    }

    QString deptInfo = QString("[%1] %2\n%3").arg(dept).arg(title).arg(content);
    QListWidgetItem *item = new QListWidgetItem(deptInfo);
    item->setToolTip(content);
    ui->lwDeptNewsList->addItem(item);

    // 新增：保存到文件
    saveInfoToFile(DeptNewsType, deptInfo);

    ui->leDeptNewsTitle->clear();
    ui->teDeptNewsContent->clear();
    QMessageBox::information(this, "发布成功", QString("%1动态已发布！").arg(dept));
}

void CampusInfoWidget::on_btnAddNotice_clicked()
{
    QString type = ui->rbtnImportant->isChecked() ? "重要事项" : "政策变更";
    QString title = ui->leNoticeTitle->text().trimmed();
    QString content = ui->teNoticeContent->toPlainText().trimmed();

    if (title.isEmpty() || content.isEmpty()) {
        QMessageBox::warning(this, "输入错误", "标题和内容不能为空！");
        return;
    }

    QString noticeInfo = QString("[%1] %2\n%3").arg(type).arg(title).arg(content);
    QListWidgetItem *item = new QListWidgetItem(noticeInfo);
    item->setForeground(ui->rbtnImportant->isChecked() ? Qt::red : Qt::blue);
    item->setToolTip(content);
    ui->lwNoticeList->addItem(item);

    // 新增：保存到文件
    saveInfoToFile(NoticeType, noticeInfo);

    ui->leNoticeTitle->clear();
    ui->teNoticeContent->clear();
    QMessageBox::information(this, "发布成功", QString("%1已发布！").arg(type));
}

void CampusInfoWidget::on_btnAddLecture_clicked()
{
    QString title = ui->leLectureTitle->text().trimmed();
    QString speaker = ui->leLectureSpeaker->text().trimmed();
    QString date = ui->deLectureDate->date().toString("yyyy-MM-dd");
    QString content = ui->teLectureContent->toPlainText().trimmed();

    if (title.isEmpty() || speaker.isEmpty() || content.isEmpty()) {
        QMessageBox::warning(this, "输入错误", "标题、主讲人、详情不能为空！");
        return;
    }

    QString lectureInfo = QString("[学术讲座] %1\n主讲人：%2\n日期：%3\n%4")
                              .arg(title).arg(speaker).arg(date).arg(content);
    QListWidgetItem *item = new QListWidgetItem(lectureInfo);
    item->setToolTip(content);
    ui->lwLectureList->addItem(item);

    // 新增：保存到文件
    saveInfoToFile(LectureType, lectureInfo);

    ui->leLectureTitle->clear();
    ui->leLectureSpeaker->clear();
    ui->teLectureContent->clear();
    QMessageBox::information(this, "发布成功", "学术讲座信息已发布！");
}

void CampusInfoWidget::on_btnSignUpLecture_clicked()
{
    if (ui->lwLectureList->currentItem() == nullptr) {
        QMessageBox::warning(this, "报名失败", "请先选择要报名的讲座！");
        return;
    }

    if (!m_lectureSignedUp) {
        m_lectureSignedUp = true;
        ui->lblSignUpStatus->setText("已报名");
        ui->lblSignUpStatus->setStyleSheet("color: green;");
        QMessageBox::information(this, "报名成功", "讲座报名成功！");
    } else {
        QMessageBox::information(this, "提示", "你已报名该讲座，无需重复报名！");
    }
}

void CampusInfoWidget::on_btnAddEmployment_clicked()
{
    QString type = ui->rbtnRecruitment->isChecked() ? "招聘会" : "实习机会";
    QString title = ui->leEmploymentTitle->text().trimmed();
    QString company = ui->leEmploymentCompany->text().trimmed();
    QString content = ui->teEmploymentContent->toPlainText().trimmed();

    if (title.isEmpty() || company.isEmpty() || content.isEmpty()) {
        QMessageBox::warning(this, "输入错误", "标题、企业名称、详情不能为空！");
        return;
    }

    QString employmentInfo = QString("[%1] %2\n企业：%3\n%4")
                                 .arg(type).arg(title).arg(company).arg(content);
    QListWidgetItem *item = new QListWidgetItem(employmentInfo);
    item->setToolTip(content);
    ui->lwEmploymentList->addItem(item);

    // 新增：保存到文件
    saveInfoToFile(EmploymentType, employmentInfo);

    ui->leEmploymentTitle->clear();
    ui->leEmploymentCompany->clear();
    ui->teEmploymentContent->clear();
    QMessageBox::information(this, "发布成功", QString("%1信息已发布！").arg(type));
}
