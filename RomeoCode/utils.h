#ifndef ROMEO_MODEL_CORE_UTILS
#define ROMEO_MODEL_CORE_UTILS

#include <QString>
#include <QDir>
#include <QKeySequence>
#include <QStringList>
#include <QImage>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <itkOpenCVImageBridge.h>
#include <itkObjectFactoryBase.h>
#include <itkImageFileReader.h>
#include <itkImage.h>
#include <itkImageLinearIteratorWithIndex.h>
#include <itkRGBPixel.h>
/*!
 *\file utils.h
 *\author Bissacco Nicolò (nickbissa@gmail.com)
 *\date 2013-02-10
*/
/*
*Changes:
*+----------+------------+-----------------+---------------------------------------------------------+---------------------------+
*|  Version +    Date    +   Programmer    +                           Changes                       +       Description         |
*+----------+------------+-----------------+---------------------------------------------------------+---------------------------+
*|          |            |                 |                                                         |                           |
*|   0.0.1  | 2013-02-10 | Bissacco Nicolò |           Romeo::Utils                                  |   First version of class  |
*|          |            |                 |                                                         |                           |
*+----------+------------+-----------------+---------------------------------------------------------+---------------------------+
*/
namespace Utils {
            /*!
             * \brief Represent the Select Type string.
             */
            static const QString ROMEO_SELECT_TYPE = "Select Type";
            /*!
             * \brief Represent the Select Featur string.
             */
            static const QString ROMEO_SELECT_FEATURE = "Select Feature";
            /*!
             * \brief Represent the Select Dataset string.
             */
            static const QString ROMEO_SELECT_DATASET = "Select Dataset";
            /*!
             * \brief Represent the Select Algorithm string.
             */
            static const QString ROMEO_SELECT_ALGORITHM = "Select Algorithm";
            /*!
             * \brief Represent the 2D string.
             */
            static const QString ROMEO_IMAGE_TYPE_2D = "2D";
            /*!
             * \brief Represent the 2D-t string.
             */
            static const QString ROMEO_IMAGE_TYPE_2Dt = "2D-t";
            /*!
             * \brief Represent the 3D string.
             */
            static const QString ROMEO_IMAGE_TYPE_3D = "3D";
            /*!
             * \brief Represent the 3D-t string.
             */
            static const QString ROMEO_IMAGE_TYPE_3Dt = "3D-t";

            /*!
             * \brief Represent the Yes string.
             */
            static const QString ROMEO_YES = "Yes";
            /*!
             * \brief Represent the No string.
             */
            static const QString ROMEO_NO = "No";

            /*!
             * \brief Represent the english date time format string.
             */
            static const QString DATETIME_FORMAT = "dd/MM/yyyy hh:mm";
            /*!
             * \brief Represent the complete english date time format string.
             */
            static const QString DATETIME_FORMAT_COMPLETE = "dd/MM/yyyy hh:mm:ss:zzz";
            /*!
             * \brief Represent the format for file string.
             */
            static const QString DATETIME_FORMAT_FILE = "yyyyMMdd_hhmm";

            /*!
             * \brief Represent the (Optional) string.
             */
            static const QString TXT_OPTIONAL = "(Optional)";
            /*!
             * \brief Represent the "*" required string.
             */
            static const QString TXT_REQUIRED = "*";

            /*!
             * \brief Represent the Romeo string.
             */
            static const QString SAVING_FOLDER = "Romeo";
            /*!
             * \brief Represent the saving folder path string.
             */
            static const QString SAVING_FOLDER_PATH = QDir::homePath()+"/"+SAVING_FOLDER;
            /*!
             * \brief Represent the name of the Subject saving folder string.
             */
            static const QString SAVING_SUBJECT_FOLDER = "Subjects";
            /*!
             * \brief Represent the complete Subject saving folder path string.
             */
            static const QString SAVING_SUBJECT_PATH = SAVING_FOLDER_PATH+"/"+SAVING_SUBJECT_FOLDER;
            /*!
             * \brief Represent the name of the Analysis saving folder string.
             */
            static const QString SAVING_ANALYSIS_FOLDER = "Analysis";
            /*!
             * \brief Represent the complete Analysis saving folder path string.
             */
            static const QString SAVING_ANALYSIS_PATH = SAVING_FOLDER_PATH+"/"+SAVING_ANALYSIS_FOLDER;

            /*!
             * \brief Represent the First Order string.
             */
            static const QString FEATURE_FIRST_ORDER = "First Order";
            /*!
             * \brief Represent the Second Order string.
             */
            static const QString FEATURE_SECOND_ORDER = "Second Order";
            /*!
             * \brief Represent the Dynamic string.
             */
            static const QString FEATURE_DYNAMIC= "Dynamic";

            /*!
             * \brief Represent the Window Size string.
             */
            static const QString FEATURE_WINDOW_SIZE = "Window Size";
            /*!
             * \brief Represent the Glcm string.
             */
            static const QString FEATURE_GLCM = " Glcm";
            /*!
             * \brief Represent the Initial Frame string.
             */
            static const QString FEATURE_INITIAL_FRAME = "Initial Frame";
            /*!
             * \brief Represent the Final Frame string.
             */
            static const QString FEATURE_FINAL_FRAME = "Final Frame";
            /*!
             * \brief Represent the (Gray Level Co-occurrence Matrix) string.
             */
            static const QString FEATURE_GLCM_FULL= "(Gray Level Co-occurrence Matrix)";

            /*!
             * \brief Represent the Mean string.
             */
            static const QString FEATURE_MEAN="Mean";
            /*!
             * \brief Represent the Standard Deviation string.
             */
            static const QString FEATURE_STANDARD_DEVIATION="Standard Deviation";
            /*!
             * \brief Represent the Skewness string.
             */
            static const QString FEATURE_SKEWNESS="Skewness";
            /*!
             * \brief Represent the Kurtosis string.
             */
            static const QString FEATURE_KURTOSIS="Kurtosis";
            /*!
             * \brief Represent the Contrast string.
             */
            static const QString FEATURE_CONTRAST="Contrast";
            /*!
             * \brief Represent the Homogeneity string.
             */
            static const QString FEATURE_HOMOGENEITY="Homogeneity";
            /*!
             * \brief Represent the Entropy string.
             */
            static const QString FEATURE_ENTROPY="Entropy";
            /*!
             * \brief Represent the Energy string.
             */
            static const QString FEATURE_ENERGY="Energy";
            /*!
             * \brief Represent the Correlation string.
             */
            static const QString FEATURE_CORRELATION="Correlation";
            /*!
             * \brief Represent the Time To Peak string.
             */
            static const QString FEATURE_TIME_TO_PEAK="Time To Peak";
            /*!
             * \brief Represent the Maximum string.
             */
            static const QString FEATURE_MAXIMUM="Maximum";
            /*!
             * \brief Represent the Minimum string.
             */
            static const QString FEATURE_MINIMUM="Minimum";
            /*!
             * \brief Represent the Slope string.
             */
            static const QString FEATURE_SLOPE="Slope";
            /*!
             * \brief Represent the Mean Dynamic string.
             */
            static const QString FEATURE_MEAN_DYNAMIC="Mean Dynamic";
            /*!
             * \brief Represent the Area Under the Curve string.
             */
            static const QString FEATURE_AREA_UNDER_CURVE="Area Under Curve";
            /*!
             * \brief Represent the Value string.
             */
            static const QString FEATURE_VALUE="Value";

            /*!
             * \brief Represent the KMeans string.
             */
            static const QString ALGORITHM_KMEANS="KMeans";
            /*!
             * \brief Represent the FuzzyCMeans string.
             */
            static const QString ALGORITHM_FUZZY="FuzzyCMeans";
            /*!
             * \brief Represent the Hierarchical string.
             */
            static const QString ALGORITHM_HIERARCHICAL="Hierarchical";

            /*!
             * \brief Represent the manage subjects shortcut.
             */
            static const QKeySequence SHORTCUT_SUBJECT_MANAGE=QKeySequence(Qt::CTRL + Qt::Key_S);
            /*!
             * \brief Represent the new subject shortcut.
             */
            static const QKeySequence SHORTCUT_SUBJECT_NEW=QKeySequence(Qt::CTRL + Qt::SHIFT + Qt::Key_S);
            /*!
             * \brief Represent the manage groups of subjects shortcut.
             */
            static const QKeySequence SHORTCUT_GROUP_MANAGE=QKeySequence(Qt::CTRL + Qt::Key_G);
            /*!
             * \brief Represent the new group of subjects shortcut.
             */
            static const QKeySequence SHORTCUT_GROUP_NEW=QKeySequence(Qt::CTRL + Qt::SHIFT + Qt::Key_G);
            /*!
             * \brief Represent the manage protocols shortcut.
             */
            static const QKeySequence SHORTCUT_PROTOCOL_MANAGE=QKeySequence(Qt::CTRL + Qt::Key_P);
            /*!
             * \brief Represent the new protocol shortcut.
             */
            static const QKeySequence SHORTCUT_PROTOCOL_NEW=QKeySequence(Qt::CTRL + Qt::SHIFT + Qt::Key_P);
            /*!
             * \brief Represent the manage datasets shortcut.
             */
            static const QKeySequence SHORTCUT_DATASET_MANAGE=QKeySequence(Qt::CTRL + Qt::Key_D);
            /*!
             * \brief Represent the new dataset shortcut.
             */
            static const QKeySequence SHORTCUT_DATASET_NEW=QKeySequence(Qt::CTRL + Qt::SHIFT + Qt::Key_D);
            /*!
             * \brief Represent the start analysis shortcut.
             */
            static const QKeySequence SHORTCUT_START_ANALYSIS=QKeySequence(Qt::CTRL + Qt::Key_A);
            /*!
             * \brief Represent the show analysis results shortcut.
             */
            static const QKeySequence SHORTCUT_RESULT_ANALYSYS=QKeySequence(Qt::CTRL + Qt::Key_R);
            /*!
             * \brief Represent the about shortcut.
             */
            static const QKeySequence SHORTCUT_ABOUT=QKeySequence(Qt::CTRL + Qt::Key_B);
            /*!
             * \brief Represent the interactive guide shortcut.
             */
            static const QKeySequence SHORTCUT_HELP_MANUAL=QKeySequence(Qt::Key_F1);
            /*!
             * \brief Represent the video guide shortcut.
             */
            static const QKeySequence SHORTCUT_HELP_VIDEO=QKeySequence(Qt::Key_F2);
            /*!
             * \brief Represent the home shortcut.
             */
            static const QKeySequence SHORTCUT_HOME=QKeySequence(Qt::CTRL + Qt::Key_H);
            /*!
             * \brief Represent the shortcuts shortcut.
             */
            static const QKeySequence SHORTCUT_SHORTCUTS=QKeySequence(Qt::Key_F3);

            /*!
             * \brief The enum AlgInputType is used to describe an integer input or a choice input.
             */
            enum AlgInputType{_INT = 1, _CHOICE = 2};


} // namespace Romeo

/*!
 * \brief The method according to the type of the file, .nii/.hdr. or .avi/.mpg, returns the image of the video (2D-t or 3D-t) or 3D image.
 * \param path represents the path of the file
 * \return Return QImage* that represents the generated image.
 */
QImage *getImage3DVideo(const QString &path);

/*!
 * \brief The method returns the image from video (2D-t).
 * \param path represents the path of the file
 * \return Return QImage* that represents the generated image.
 */
QImage *get2DtFrom(const QString &path);

/*!
 * \brief The method returns the image from 3D image.
 * \param path represents the path of the file
 * \return Return QImage* that represents the generated image.
 */
QImage *get3DFrom(const QString &path);

/*!
 * \brief The method returns the image from 3D video (3D-t).
 * \param path represents the path of the file
 * \return Return QImage* that represents the generated image.
 */
QImage *get3DtFrom(const QString &path);

/*!
 * \brief The method tests if the file 3D passed as a parameter is a 3D video or 3D image.
 * \param path represents the path of the file
 * \return Return true if the file is a video otherwise return false.
 */
bool check3DVideo(const QString &path);

/*!
 * \brief Create a path in the main directory if it doesn't already exists.
 * \param path represent the name of the path
 * \return Return true if successful otherwise returns false.
 */
bool checkPathExistsFromHome(const QString & path);

/*!
 * \brief copyDir method copy the source folder to destination folder.
 * \param source is the source folder.
 * \param destination is the destinations folder.
 * \param override true if override existing files, false if not.
 * \return Return true if copy succedded, false if error occurred.
 */
bool copyDir(const QString source, const QString destination, const bool override);

#endif // ROMEO_MODEL_CORE_UTILS
