#include "apanel.h"
#include "utils.h"

using Romeo::View::Window::APanel;

APanel::APanel(QWidget *parent) : QWidget(parent), showToolbar(true), resultMessageWidget(0) {
    setObjectName("APanel");    
}

//destructor of the class
APanel::~APanel() {
}

void APanel::initializeView() {

    setupView();
    setupLayout();
    setupObjectName();
    addConnect();
    loadCss();
    setupToolTip();
}

QStringListModel * APanel::getTypeRomeo(QObject *parent)
{
    QStringList items;
    items << Utils::ROMEO_SELECT_TYPE << Utils::ROMEO_IMAGE_TYPE_2D << Utils::ROMEO_IMAGE_TYPE_2Dt << Utils::ROMEO_IMAGE_TYPE_3D << Utils::ROMEO_IMAGE_TYPE_3Dt;
    return new QStringListModel(items, parent);
}

void APanel::addResultMessageWidget(const QString& txt, bool type) {
}

void APanel::removeResultMessageWidget() {
    if(resultMessageWidget){
        delete resultMessageWidget;
        resultMessageWidget = 0;
    }
}

ResultMessageWidget * APanel::getResultMessageWidget() const {
    return resultMessageWidget;
}

QLabel * APanel::labelInfo(const QString& txt, QWidget * parent) const{
    QSizePolicy policyInfo(QSizePolicy::Preferred, QSizePolicy::Fixed);
    policyInfo.setHorizontalStretch(0);
    policyInfo.setVerticalStretch(0);

    QLabel *label=new QLabel(txt, parent);
    label->setObjectName("formInfo");
    label->setSizePolicy(policyInfo);
    label->setWordWrap(true);

    return label;
}

QLabel * APanel::labelEmpty(const QString& txt, QWidget * parent) const{
    QSizePolicy policyInfo(QSizePolicy::Preferred, QSizePolicy::Fixed);
    policyInfo.setHorizontalStretch(0);
    policyInfo.setVerticalStretch(0);

    QLabel *label=new QLabel(txt, parent);
    label->setObjectName("labelEmpty");
    label->setSizePolicy(policyInfo);
    label->setWordWrap(true);

    return label;
}

bool APanel::isShowToolbar() const {
    return showToolbar;
}

void APanel::setShowToolbar(bool show) {
    showToolbar = show;
}
