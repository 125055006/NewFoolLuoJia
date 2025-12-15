#include "campusinfowidget.h"
#include "ui_campusinfowidget.h"

CampusInfoWidget::CampusInfoWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CampusInfoWidget)
{
    ui->setupUi(this);
    // 初始化：设置默认选中项、报名状态默认显示
    ui->rbtnImportant->setChecked(true);
    ui->rbtnRecruitment->setChecked(true);
    ui->lblSignUpStatus->setText("未报名");
    ui->lblSignUpStatus->setStyleSheet("color: red;");

    // 初始化院系下拉框
    ui->cbxDept->addItems({"计算机学院", "文学院", "理学院", "工学院", "商学院"});
}

CampusInfoWidget::~CampusInfoWidget()
{
    delete ui;
}
// ---------------------- 校园要闻：发布逻辑 ----------------------
void CampusInfoWidget::on_btnAddCampusNews_clicked()
{
    QString title = ui->leCampusNewsTitle->text().trimmed();
    QString content = ui->teCampusNewsContent->toPlainText().trimmed();

    // 空值校验
    if (title.isEmpty() || content.isEmpty()) {
        QMessageBox::warning(this, "输入错误", "标题和内容不能为空！");
        return;
    }

    // 拼接信息并添加到列表
    QString newsInfo = QString("[校园要闻] %1\n%2").arg(title).arg(content);
    QListWidgetItem *item = new QListWidgetItem(newsInfo);
    item->setToolTip(content); // 鼠标悬浮显示完整内容
    ui->lwCampusNewsList->addItem(item);

    // 清空输入框
    ui->leCampusNewsTitle->clear();
    ui->teCampusNewsContent->clear();

    QMessageBox::information(this, "发布成功", "校园要闻已发布！");
}

// ---------------------- 院系动态：发布逻辑 ----------------------
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

    ui->leDeptNewsTitle->clear();
    ui->teDeptNewsContent->clear();

    QMessageBox::information(this, "发布成功", QString("%1动态已发布！").arg(dept));
}

// ---------------------- 通知公告：发布逻辑 ----------------------
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
    // 重要事项标红，政策变更标蓝
    item->setForeground(ui->rbtnImportant->isChecked() ? Qt::red : Qt::blue);
    item->setToolTip(content);
    ui->lwNoticeList->addItem(item);

    ui->leNoticeTitle->clear();
    ui->teNoticeContent->clear();

    QMessageBox::information(this, "发布成功", QString("%1已发布！").arg(type));
}

// ---------------------- 学术讲座：发布逻辑 ----------------------
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

    ui->leLectureTitle->clear();
    ui->leLectureSpeaker->clear();
    ui->teLectureContent->clear();

    QMessageBox::information(this, "发布成功", "学术讲座信息已发布！");
}

// ---------------------- 学术讲座：报名逻辑 ----------------------
void CampusInfoWidget::on_btnSignUpLecture_clicked()
{
    // 校验是否有选中的讲座
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

// ---------------------- 就业信息：发布逻辑 ----------------------
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

    ui->leEmploymentTitle->clear();
    ui->leEmploymentCompany->clear();
    ui->teEmploymentContent->clear();

    QMessageBox::information(this, "发布成功", QString("%1信息已发布！").arg(type));
}
