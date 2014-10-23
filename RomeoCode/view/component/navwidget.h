#ifndef ROMEO_VIEW_COMPONENT_NAVWIDGET_H
#define ROMEO_VIEW_COMPONENT_NAVWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QDialogButtonBox>
#include <QHBoxLayout>
#include "view/window/apanel.h"
#include "view/window/mainwindow.h"

using Romeo::View::Window::APanel;
/*!
 *\file navwidget.h
 *\author Bissacco Nicolò (nickbissa@gmail.com)
 *\date 2013-02-10
*/
/*
*Changes:
*+----------+------------+-----------------+-----------------------------------------------------+---------------------------+
*|  Version +    Date    +   Programmer    +                       Changes                       +       Description         |
*+----------+------------+-----------------+-----------------------------------------------------+---------------------------+
*|          |            |                 |                                                     |                           |
*|   0.0.1  | 2013-02-10 | Bissacco Nicolò |         RomeoView::Component::NavWidget             |   First version of class  |
*|          |            |                 |                                                     |                           |
*+----------+------------+-----------------+-----------------------------------------------------+---------------------------+
*/
namespace Romeo {

    namespace View {

        namespace Component {

        /*!
             * \brief The NavWidget class provides a widget composed at least of two buttons: the "Back" button
             * for going back to the previous window and the "Help" button for visualize user guide.
             * It's possible to create widget composed of several combinations of buttons.
             */
            class NavWidget : public QWidget
            {
            public:
                /*!
                 * \brief The enum type is used to describe which buttons will be displayed in the widget. It contains the combinations:
                 * only back button;
                 * back and save buttons;
                 * back and edit buttons,
                 * back, edit and delete buttons,
                 * back and delete buttons,
                 * back and start analysis buttons,
                 * back, restart analysis and show analysis results button.
                 */
                enum Type{_ONLY_BACK = 1, _BACK_SAVE = 2, _BACK_EDIT = 3, _BACK_EDIT_DELETE = 4, _BACK_DELETE = 5, _BACK_START_ANALYSIS = 6, _BACK_RESTART_SHOW = 7, _BACK_EXPORT = 8};

                /*!
                 * \brief Construct a NavWidget with the given type and parent.
                 * \param type represent which buttons will be displayed in the widget.
                 * \param parent represent the parent of the NavWidget object.
                 */
                NavWidget(Type type = _BACK_SAVE, APanel *parent =0);

                /*!
                 * \brief The method set the property enabled of back button with the given enable parameter.
                 * \param enable represent if the button is enabled or not.
                 */
                void setEnableBack(bool enable = true);
                /*!
                 * \brief The method set the property enabled of edit button with the given enable parameter.
                 * \param enable represent if the button is enabled or not.
                 */
                void setEnableEdit(bool enable = true);
                /*!
                 * \brief The method set the property enabled of save button with the given enable parameter.
                 * \param enable represent if the button is enabled or not.
                 */
                void setEnableSave(bool enable = true);
                /*!
                 * \brief The method set the property enabled of delete button with the given enable parameter.
                 * \param enable represent if the button is enabled or not.
                 */
                void setEnableDelete(bool enable = true);
                /*!
                 * \brief The method set the property enabled of start analysis button with the given enable parameter.
                 * \param enable represent if the button is enabled or not.
                 */
                void setEnableStartAnalysis(bool enable = true);
                /*!
                 * \brief The method set the property enabled of restart analysis button with the given enable parameter.
                 * \param enable represent if the button is enabled or not.
                 */
                void setEnableRestart(bool enable = true);
                /*!
                 * \brief The method set the property enabled of show analysis results button with the given enable parameter.
                 * \param enable represent if the button is enabled or not.
                 */
                void setEnableShow(bool enable = true);
                /*!
                 * \brief The method set the property enabled of help button with the given enable parameter.
                 * \param enable represent if the button is enabled or not.
                 */
                void setEnableHelp(bool enable = true);

                private:
                    QWidget *navContainer;
                        QPushButton *backButton;
                        QPushButton *editButton;
                        QPushButton *saveButton;
                        QPushButton *deleteButton;
                        QPushButton *startAnalysisButton;
                        QPushButton *restartButton;
                        QPushButton *showButton;
                        QPushButton *exportButton;
                    QWidget *helpContainer;
                        QPushButton *helpButton;

                    /*!
                     * \brief The method create the back button, add it to the given layout and set the enabled property.
                     * \param layout represents which layout the button will be added.
                     * \param parent represents the parent of the button object.
                     * \param enable represents if the button will be enabled or disabled by default.
                     */
                    void createBackButton(QHBoxLayout *layout, QWidget* parent, bool enable = true);
                    /*!
                     * \brief The method create the edit button, add it to the given layout and set the enabled property.
                     * \param layout represents which layout the button will be added.
                     * \param parent represents the parent of the button object.
                     * \param enable represents if the button will be enabled or disabled by default.
                     */
                    void createEditButton(QHBoxLayout *layout, QWidget* parent, bool enable = true);
                    /*!
                     * \brief The method create the save button, add it to the given layout and set the enabled property.
                     * \param layout represents which layout the button will be added.
                     * \param parent represents the parent of the button object.
                     * \param enable represents if the button will be enabled or disabled by default.
                     */
                    void createSaveButton(QHBoxLayout *layout, QWidget* parent, bool enable = true);
                    /*!
                     * \brief The method create the delete button, add it to the given layout and set the enabled property.
                     * \param layout represents which layout the button will be added.
                     * \param parent represents the parent of the button object.
                     * \param enable represents if the button will be enabled or disabled by default.
                     */
                    void createDeleteButton(QHBoxLayout *layout, QWidget* parent, bool enable = true);
                    /*!
                     * \brief The method create the help button, add it to the given layout and set the enabled property.
                     * \param layout represents which layout the button will be added.
                     * \param parent represents the parent of the button object.
                     * \param enable represents if the button will be enabled or disabled by default.
                     */
                    void createHelpButton(QHBoxLayout *layout, QWidget* parent, bool enable = true);
                    /*!
                     * \brief The method create the start analysis button, add it to the given layout and set the enabled property.
                     * \param layout represents which layout the button will be added.
                     * \param parent represents the parent of the button object.
                     * \param enable represents if the button will be enabled or disabled by default.
                     */
                    void createStartAnalysisButton(QHBoxLayout *layout, QWidget* parent, bool enable = true);
                    /*!
                     * \brief The method create the restart analysis button, add it to the given layout and set the enabled property.
                     * \param layout represents which layout the button will be added.
                     * \param parent represents the parent of the button object.
                     * \param enable represents if the button will be enabled or disabled by default.
                     */
                    void createRestartButton(QHBoxLayout *layout, QWidget* parent, bool enable = true);
                    /*!
                     * \brief The method create the show analysis results button, add it to the given layout and set the enabled property.
                     * \param layout represents which layout the button will be added.
                     * \param parent represents the parent of the button object.
                     * \param enable represents if the button will be enabled or disabled by default.
                     */
                    void createShowButton(QHBoxLayout *layout, QWidget* parent, bool enable = true);
                                        /*!
                     * \brief The method create the export button, add it to the given layout and set the enabled property.
                     * \param layout represents which layout the button will be added.
                     * \param parent represents the parent of the button object.
                     * \param enable represents if the button will be enabled or disabled by default.
                     */
                    void createExportButton(QHBoxLayout *layout, QWidget* parent, bool enable = true);
                    /*!
                     * \brief The method add the object name to the Qt object.
                     */
                    void setupObjectsName();
                    /*!
                     * \brief The method create the button based on type parameter.
                     * \param type represent which buttons will be displayed in the widget.
                     * \param navContainerLayout represent the layout for the navigations buttons.
                     * \param helpContainerLayout represent the layout for the help button.
                     */
                    void create(Type type, QHBoxLayout *navContainerLayout, QHBoxLayout *helpContainerLayout);
            };

        } // namespace Component

    } // namespace View

} // namespace Romeo

#endif // ROMEO_VIEW_COMPONENT_NAVWIDGET_H
