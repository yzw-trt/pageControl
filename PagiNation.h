#ifndef PAGINATION_H
#define PAGINATION_H

#include <cmath>

#include <QFrame>
#include <QLayout>
#include <QPushButton>
#include <QLabel>
#include <QDebug>

#include <QMetaMethod>

using namespace std;

/** 水平对齐方式枚举 */
enum AlignType {
    Align_Left,
    Align_Right,
    Align_Center
};

struct __PagiNation_DATA {
    int type; // 1: 按钮  2: 点
    int labelNum;
    bool choosed;
};

class Button: public QPushButton {
    Q_OBJECT
    public:
        Button (QString text, QWidget *parent);

    public:
        void setChecked (bool checked);

    signals:
        void cClick (Button*);

    private slots:
        void handleClick ();
};

class PagiNation: public QFrame {
    Q_OBJECT
    public:
        PagiNation (QWidget *parent, AlignType align = AlignType::Align_Right, int buttonCount = 7);
        PagiNation (QPoint point, QWidget *parent, AlignType align = AlignType::Align_Right, int buttonCount = 7);
        PagiNation (QSize size, QWidget *parent, AlignType align = AlignType::Align_Right, int buttonCount = 7);
        PagiNation (QRect rect, QWidget *parent, AlignType align = AlignType::Align_Right, int buttonCount = 7);

    private:
        AlignType _align;
        int _buttonCount;
        int _height;
        QHBoxLayout *BJ, *BJ_main;
        QSpacerItem *TH_left, *TH_right;
        int _pageNow = 1, _total = 0, _pageSize = 10;
        QPushButton *prevBtn, *nextBtn, *prevFBtn, *nextFBtn;
        QFrame *mainBox;

    signals:
        /** 页码变更信号 */
        void pageChanged (int pageNow, int pageSize);

    public:
        /** 获取当前页码 page */
        int page ();
        /** 获取当前每页条数 pagesize */
        int pageSize ();
        /** 获取当前数据总条数 pagesize */
        int total ();
        /** 获取当前最大按钮数 pagesize */
        int buttonCount ();
        /** 获取当前对齐方式 pagesize */
        AlignType alignment ();
        /** 设置最大按钮数量 */
        void setButtonCount (int buttonCount, bool needEmit = false);
        /** 设置左右对齐方式 */
        void setAlign (AlignType align, bool needEmit = false);
        /** 设置每页条数 */
        void setPageSize (int pageSize, bool needEmit = false);
        /** 设置总条数(用于计算总页数) */
        void setTotal (int total, bool needEmit = false);
        /** 设置页码 */
        void setPage (int pageNow, bool needEmit = false);
        /** 设置页码 */
        void setPage (int pageNow, int total, bool needEmit = false);
        /** 连接 "页码变更" 信号 */
        void connectPageChange (function<void(int, int)> method);
        /** 连接 "页码变更" 信号 */
        void connectPageChange (function<void(int)> method);
        /** 连接 "页码变更" 信号 */
        void connectPageChange (function<void()> method);

    private:
        void init ();
        /** 计算当前页码展示 */
        void computePage ();
        /** 渲染按钮列表 */
        void renderBtn (QList<__PagiNation_DATA> list);
        /** 设置控件对齐 */
        void setWidgetAlign ();

    private slots:
        /** 点击页码按钮 槽函数 */
        void handleClick (Button *self);
        /** 页码后退1 */
        void toPrev1 ();
        /** 页码后退5 */
        void toPrev5 ();
        /** 页码前进1 */
        void toNext1 ();
        /** 页码前进5 */
        void toNext5 ();
};

#endif // PAGINATION_H
