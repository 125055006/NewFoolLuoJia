#include "messagecenter.h"
#include "ui_messagecenter.h"
#include <QListWidgetItem>
#include <QMessageBox>
#include <QDateTime>

MessageCenter::MessageCenter(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MessageCenter)
{
    ui->setupUi(this);
    //连接的槽函数
    connect(ui->AllNotification, &QPushButton::clicked,
            this, &MessageCenter::on_AllNotification_clicked);
    connect(ui->Notification, &QPushButton::clicked,
            this, &MessageCenter::on_Notification_clicked);
    connect(ui->Todo, &QPushButton::clicked,
            this, &MessageCenter::on_Todo_clicked);
    connect(ui->Content, &QListWidget::itemDoubleClicked,
            this, &MessageCenter::on_Content_itemDoubleClicked);

    //默认“全部”打开
    on_AllNotification_clicked();

    //为了美观进行设置字体
    defaultStyle =
        "QPushButton {"
        "   font-family: 'Microsoft YaHei', 'Segoe UI', Arial;"
        "   font-size: 16px;"                     // 增大字体
        "   font-weight: 600;"                    // 加粗（600是半粗体）
        "   padding: 12px 0;"                     // 内边距
        "   border: 2px solid #dee2e6;"          // 边框
        "   border-radius: 6px;"                 // 圆角
        "   background-color: #f8f9fa;"          // 默认背景色
        "   color: #212529;"                     // 黑色文字
        "}"
        "QPushButton:hover {"
        "   background-color: #e9ecef;"          // 悬停效果
        "   border-color: #adb5bd;"
        "}"
        "QPushButton:pressed {"
        "   background-color: #dee2e6;"          // 按下效果
        "}";

    selectedStyle =
        "QPushButton {"
        "   font-family: 'Microsoft YaHei';"
        "   font-size: 16px;"
        "   font-weight: 700;"                    // 选中加粗
        "   padding: 12px 0;"
        "   border: 2px solid #007bff;"          // 蓝色边框
        "   border-radius: 6px;"
        "   background-color: #007bff;"          // 蓝色背景
        "   color: white;"                       // 白色文字
        "}";

    ui->AllNotification->setStyleSheet(defaultStyle);
    ui->Notification->setStyleSheet(defaultStyle);
    ui->Todo->setStyleSheet(defaultStyle);//将美化操作全部添加到按钮
}

MessageCenter::~MessageCenter()
{
    delete ui;
}

void MessageCenter::on_AllNotification_clicked()
{
    ui->Content->clear();//清理当前界面

    QListWidgetItem *item1 = new QListWidgetItem("📋 [全部] 系统通知 - 登录成功");
    QListWidgetItem *item2 = new QListWidgetItem("📋 [全部] 待办事项 - 完成报告");
    QListWidgetItem *item3 = new QListWidgetItem("📋 [全部] 系统通知 - 安全提醒");
    QListWidgetItem *item4 = new QListWidgetItem("📋 [全部] 待办事项 - 参加会议");

    ui->Content->addItem(item1);
    ui->Content->addItem(item2);
    ui->Content->addItem(item3);
    ui->Content->addItem(item4);//添加一些本地测试的数据

    ui->AllNotification->setStyleSheet(selectedStyle);
    ui->Notification->setStyleSheet(defaultStyle);
    ui->Todo->setStyleSheet(defaultStyle);//提示当前选择按钮
    //设置ListItem的大小等美观
    ui->Content->setStyleSheet(
        "QListWidget {"
        "   border: 2px solid #dee2e6;"
        "   border-radius: 8px;"
        "   background-color: #ffffff;"
        "}"
        "QListWidget::item {"
        "   border-bottom: 1px solid #f0f0f0;"  // 分隔线
        "   padding: 15px 10px;"                // 增加内边距
        "}"
        "QListWidget::item:hover {"
        "   background-color: #f8f9fa;"         // 悬停效果
        "}"
        "QListWidget::item:selected {"
        "   background-color: #e7f3ff;"         // 选中效果
        "   color: #0066cc;"
        "}"
        );
}


void MessageCenter::on_Notification_clicked()
{
    ui->Content->clear();//同样清楚界面

    QListWidgetItem *item1 = new QListWidgetItem("🔔 [通知] 系统通知 - 登录成功");
    QListWidgetItem *item2 = new QListWidgetItem("🔔 [通知] 安全提醒 - 异常登录检测");
    QListWidgetItem *item3 = new QListWidgetItem("🔔 [通知] 系统更新 - 新版本发布");

    ui->Content->addItem(item1);
    ui->Content->addItem(item2);
    ui->Content->addItem(item3);//添加属于“通知”的本次数据

    ui->AllNotification->setStyleSheet(defaultStyle);
    ui->Notification->setStyleSheet(selectedStyle);
    ui->Todo->setStyleSheet(defaultStyle);//提示当前选择按钮
}


void MessageCenter::on_Todo_clicked()
{
    ui->Content->clear();

    QListWidgetItem *item1 = new QListWidgetItem("✅ [待办] 完成项目报告");
    QListWidgetItem *item2 = new QListWidgetItem("✅ [待办] 参加项目评审会议");
    QListWidgetItem *item3 = new QListWidgetItem("✅ [待办] 代码审查");
    QListWidgetItem *item4 = new QListWidgetItem("✅ [待办] 提交设计文档");

    ui->Content->addItem(item1);
    ui->Content->addItem(item2);
    ui->Content->addItem(item3);
    ui->Content->addItem(item4);

    ui->AllNotification->setStyleSheet(defaultStyle);
    ui->Notification->setStyleSheet(defaultStyle);
    ui->Todo->setStyleSheet(selectedStyle);
}


void MessageCenter::on_Content_itemDoubleClicked(QListWidgetItem *item)
{
    on_Content_itemClicked(item);//实现单击的函数
}


void MessageCenter::on_Content_itemClicked(QListWidgetItem *item)
{
    if (!item) return;

    QString itemText = item->text();
    //添加点击进入的内容
    if (itemText.contains("安全提醒 - 异常登录检测")) {
        QMessageBox::information(this, "安全提醒详情",
                                 "🔒 异常登录检测\n\n"
                                 "⚠️ 检测到可疑登录行为：\n"
                                 "• 登录IP: 192.168.1.100 (武汉)\n"
                                 "• 登录时间: 2025-12-15 14:30\n"
                                 "• 设备类型: Windows 10\n"
                                 "• 浏览器: Chrome 120.0\n\n"
                                 "🔐 安全建议：\n"
                                 "1. 请确认是否是您本人操作\n"
                                 "2. 如非本人操作，请立即修改密码\n"
                                 "3. 建议开启双重验证\n");
    }
    else if (itemText.contains("系统通知 - 登录成功")) {
        QMessageBox::information(this, "登录通知详情",
                                 "✅ 登录成功通知\n\n"
                                 "您的账户已成功登录：\n"
                                 "• 登录时间: 2024-01-15 10:30\n"
                                 "• 登录设备: 您的常用设备\n"
                                 "• 登录地点: 上海市\n\n"
                                 "如有疑问，请联系客服。");
    }
    else if (itemText.contains("待办事项 - 完成报告")) {
        QMessageBox::information(this, "待办事项详情",
                                 "📋 完成项目报告\n\n"
                                 "任务详情：\n"
                                 "• 任务名称: 项目进度报告\n"
                                 "• 截止时间: 今天 18:00\n"
                                 "• 负责人: 您\n"
                                 "• 优先级: 高\n\n"
                                 "📝 要求：\n"
                                 "1. 总结本周项目进展\n"
                                 "2. 列出遇到的问题\n"
                                 "3. 提出下周计划\n"
                                 "4. 提交至项目管理平台");
    }
    else if (itemText.contains("待办事项 - 参加会议")) {
        QMessageBox::information(this, "会议提醒详情",
                                 "👥 项目评审会议\n\n"
                                 "会议信息：\n"
                                 "• 会议时间: 今天 14:00-15:30\n"
                                 "• 会议地点: 3号会议室\n"
                                 "• 主持人: 张经理\n"
                                 "• 参会人员: 项目组全体成员\n\n"
                                 "📋 会议议题：\n"
                                 "1. 项目进度汇报\n"
                                 "2. 技术方案讨论\n"
                                 "3. 下周工作计划\n\n"
                                 "请提前10分钟到场。");
    }
    else if (itemText.contains("系统更新 - 新版本发布")) {
        QMessageBox::information(this, "系统更新详情",
                                 "🔄 新版本发布通知\n\n"
                                 "版本号: v2.1.0\n"
                                 "发布时间: 2024-01-15\n"
                                 "更新大小: 约 50MB\n\n"
                                 "✨ 新功能：\n"
                                 "• 新增消息中心功能\n"
                                 "• 优化用户界面\n"
                                 "• 提升系统性能\n\n"
                                 "🐛 修复问题：\n"
                                 "• 修复了已知的若干bug\n"
                                 "• 提升了系统稳定性\n\n"
                                 "建议尽快更新以获取最佳体验。");
    }
    else if (itemText.contains("代码审查")) {
        QMessageBox::information(this, "代码审查任务",
                                 "👨‍💻 代码审查任务\n\n"
                                 "任务详情：\n"
                                 "• 审查人员: 您\n"
                                 "• 提交人: 同事张三\n"
                                 "• 提交时间: 昨天 16:00\n"
                                 "• 代码分支: feature/user-manage\n\n"
                                 "📋 审查要点：\n"
                                 "1. 代码规范性\n"
                                 "2. 功能完整性\n"
                                 "3. 性能优化\n"
                                 "4. 安全考虑\n\n"
                                 "请在今天内完成审查。");
    }
    else if (itemText.contains("提交设计文档")) {
        QMessageBox::information(this, "文档提交任务",
                                 "📄 设计文档提交\n\n"
                                 "任务详情：\n"
                                 "• 文档名称: 系统设计文档_v2.0\n"
                                 "• 截止时间: 下周一 17:00\n"
                                 "• 提交方式: 邮件发送给李总监\n\n"
                                 "📝 文档要求：\n"
                                 "1. 包含系统架构图\n"
                                 "2. 详细的功能说明\n"
                                 "3. 数据库设计\n"
                                 "4. 接口文档\n"
                                 "5. 部署方案\n\n"
                                 "请按时完成并提交。");
    }
    else {
        // 默认处理
        QMessageBox::information(this, "消息详情",
                                 QString("消息内容：\n\n%1\n\n点击时间：%2")
                                     .arg(itemText,QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")));
    }
}

