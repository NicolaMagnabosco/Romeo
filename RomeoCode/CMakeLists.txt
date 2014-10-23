PROJECT(Romeo)
CMAKE_MINIMUM_REQUIRED(VERSION 2.8.9)
 cmake_policy(SET CMP0020 NEW)
aux_source_directory(. SRC_LIST)


SET(CMAKE_INCLUDE_CURRENT_DIR ON)
SET(CMAKE_AUTOMOC ON)
SET(CMAKE_BUILD_TYPE "Release")

if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall")
endif()

#FIN QT PACKAGE
FIND_PACKAGE(Qt5Widgets)
FIND_PACKAGE(Qt5Core)
FIND_PACKAGE(Qt5Gui)
FIND_PACKAGE(Qt5Sql)
FIND_PACKAGE(Qt5Help)



#INCLUDE ITK LIBRERIES
FIND_PACKAGE(ITK REQUIRED)
IF (ITK_FOUND)
       INCLUDE( ${USE_ITK_FILE} )
ENDIF(ITK_FOUND)


#INCLUDE BOOST LIBRARIES
set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost 1.45.0 COMPONENTS thread system log log_setup program_options)
include_directories(${Boost_INCLUDE_DIR})


#INCLUDE OPENCV LIBRARIES
FIND_PACKAGE(OpenCV REQUIRED)
include_directories( ${OpenCV_INCLUDE_DIRS} )

#INCLUDE QT
INCLUDE_DIRECTORIES(${Qt5Widgets_INCLUDE_DIR} ${Qt5Core_INCLUDE_DIR} ${Qt5Gui_INCLUDE_DIR} ${Qt5Sql_INCLUDE_DIR})

#SET A VARIABLE WITH ALL HEADER FILES
SET (headers
    utils.h
    controller/acontroller.h
    controller/analysiscontroller.h
    controller/controllermanager.h
    controller/datasetscontroller.h
    controller/detailedresultcontroller.h
    controller/groupscontroller.h
    controller/mainwindowcontroller.h
    controller/newdatasetcontroller.h
    controller/newgroupcontroller.h
    controller/newprotocolcontroller.h
    controller/newsubjectcontroller.h
    controller/protocolscontroller.h
    controller/resultscontroller.h
    controller/subjectscontroller.h
    controller/welcomecontroller.h
    model/core/algcreator.h
    model/core/algorithm/aalgorithm.h
    model/core/analysis.h
    model/core/asubject.h
    model/core/asubject.h
    model/core/dataset.h
    model/core/featcreator.h
    model/core/feature/afeature.h
    model/core/feature/contrastfeature.h
    model/core/feature/correlationfeature.h
    model/core/feature/dynamicfeature.h
    model/core/feature/energyfeature.h
    model/core/feature/entropyfeature.h
    model/core/feature/firstorderfeature.h
    model/core/feature/homogeneityfeature.h
    model/core/feature/kurtosisfeature.h
    model/core/feature/maximumfeature.h
    model/core/feature/meanfeature.h
    model/core/feature/meandynamicfeature.h
    model/core/feature/minimumfeature.h
    model/core/feature/secondorderfeature.h
    model/core/feature/skewnessfeature.h
    model/core/feature/standarddeviationfeature.h
    model/core/feature/standarddeviationfeature.h
    model/core/feature/areaundercurvefeature.h
    model/core/groupofsubject.h
    model/core/internaldata.h
    model/core/internaldata2d.h
    model/core/internaldata3d.h
    model/core/isubject.h
    model/core/protocol.h
    model/core/proxysubject.h
    model/core/realsubject.h
    model/core/realsubjectimage.h
    model/core/realsubjectvideo.h
    model/core/rgbimage.h
    model/core/rgbimage2d.h
    model/core/rgbimage3d.h
    model/core/video2d.h
    model/core/video3d.h
    model/qtModel/tablemodel.h
    model/qtModel/analysisprotocolstablemodel.h
    model/qtModel/analysissubjectstablemodel.h
    model/qtModel/datasetstablemodel.h
    model/qtModel/datasetgrouptablemodel.h
    model/qtModel/datasetprotocoltablemodel.h
    model/qtModel/groupsubjectstablemodel.h
    model/qtModel/grouptablemodel.h
    model/qtModel/newgrouptablemodel.h
    model/qtModel/newprotocolfeaturetablemodel.h
    model/qtModel/protocoltablemodel.h
    model/qtModel/resultstablemodel.h
    model/qtModel/subjecttablemodel.h
    model/util/dao/adatabase.h
    model/util/dao/algorithmdao.h
    model/util/dao/analysisdao.h
    model/util/dao/datasetdao.h
    model/util/dao/featuredao.h
    model/util/dao/groupdao.h
    model/util/dao/protocoldao.h
    model/util/dao/subjectdao.h
    model/util/exporterModel/exporter.h
    model/util/exporterModel/exporter2d.h
    model/util/exporterModel/exporter3d.h
    model/util/log/log.h
    model/util/readerModel/imagereader.h
    model/util/readerModel/reader.h
    model/util/readerModel/videoreader.h
    view/component/imagelabel.h
    view/component/navwidget.h
    view/component/selectdeselectwidget.h
    view/component/resultmessagewidget.h
    view/component/toolbar.h
    view/dialog/analysisdialog.h
    view/dialog/dialog.h
    view/dialog/featureparams.h
    view/window/analysisview.h
    view/window/apanel.h
    view/window/datasetsview.h
    view/window/detailedresult.h
    view/window/groupview.h
    view/window/mainwindow.h
    view/window/newdatasetview.h
    view/window/newgroupview.h
    view/window/newprotocolview.h
    view/window/newsubjectview.h
    view/window/protocolsview.h
    view/window/resultsview.h
    view/window/subjectsview.h
    view/window/welcomeview.h
    model/core/algorithm/fuzzycmeansalgorithm.h
    model/core/algorithm/kmeansalgorithm.h
    model/core/algorithm/clusterpoint.h
    model/core/algorithm/clusterpoint2d.h
    model/core/algorithm/clusterpoint3d.h
    model/core/algorithm/clustercentroid.h
    model/core/algorithm/clustercentroid2d.h
    model/core/algorithm/clustercentroid3d.h
    model/core/algorithm/fuzzycmeans.h
    model/core/algorithm/fuzzycmeans3d.h
    model/help/assistant.h
    model/core/romeoobject.h
    model/core/video.h)

#SET A VARIABLE WITH ALL THE CPP FILES
SET (sources
    main.cpp
    utils.cpp
    controller/acontroller.cpp
    controller/analysiscontroller.cpp
    controller/controllermanager.cpp
    controller/datasetscontroller.cpp
    controller/detailedresultcontroller.cpp
    controller/groupscontroller.cpp
    controller/mainwindowcontroller.cpp
    controller/newdatasetcontroller.cpp
    controller/newgroupcontroller.cpp
    controller/newprotocolcontroller.cpp
    controller/newsubjectcontroller.cpp
    controller/protocolscontroller.cpp
    controller/resultscontroller.cpp
    controller/subjectscontroller.cpp
    controller/welcomecontroller.cpp
    model/core/algcreator.cpp
    model/core/algorithm/aalgorithm.cpp
    model/core/analysis.cpp
    model/core/asubject.cpp
    model/core/dataset.cpp
    model/core/featcreator.cpp
    model/core/feature/afeature.cpp
    model/core/feature/contrastfeature.cpp
    model/core/feature/correlationfeature.cpp
    model/core/feature/dynamicfeature.cpp
    model/core/feature/energyfeature.cpp
    model/core/feature/entropyfeature.cpp
    model/core/feature/firstorderfeature.cpp
    model/core/feature/homogeneityfeature.cpp
    model/core/feature/kurtosisfeature.cpp
    model/core/feature/maximumfeature.cpp
    model/core/feature/meanfeature.cpp
    model/core/feature/meandynamicfeature.cpp
    model/core/feature/minimumfeature.cpp
    model/core/feature/secondorderfeature.cpp
    model/core/feature/skewnessfeature.cpp
    model/core/feature/standarddeviationfeature.cpp
    model/core/feature/standarddeviationfeature.cpp
    model/core/feature/areaundercurvefeature.cpp
    model/core/groupofsubject.cpp
    model/core/internaldata.cpp
    model/core/internaldata2d.cpp
    model/core/internaldata3d.cpp
    model/core/isubject.cpp
    model/core/protocol.cpp
    model/core/proxysubject.cpp
    model/core/realsubject.cpp
    model/core/realsubjectimage.cpp
    model/core/realsubjectvideo.cpp
    model/core/rgbimage2d.cpp
    model/core/rgbimage3d.cpp
    model/core/video2d.cpp
    model/core/video3d.cpp
    model/qtModel/tablemodel.cpp
    model/qtModel/analysisprotocolstablemodel.cpp
    model/qtModel/analysissubjectstablemodel.cpp
    model/qtModel/datasetstablemodel.cpp
    model/qtModel/datasetgrouptablemodel.cpp
    model/qtModel/datasetprotocoltablemodel.cpp
    model/qtModel/groupsubjectstablemodel.cpp
    model/qtModel/grouptablemodel.cpp
    model/qtModel/newgrouptablemodel.cpp
    model/qtModel/newprotocolfeaturetablemodel.cpp
    model/qtModel/protocoltablemodel.cpp
    model/qtModel/resultstablemodel.cpp
    model/qtModel/subjecttablemodel.cpp
    model/util/dao/adatabase.cpp
    model/util/dao/algorithmdao.cpp
    model/util/dao/analysisdao.cpp
    model/util/dao/datasetdao.cpp
    model/util/dao/featuredao.cpp
    model/util/dao/groupdao.cpp
    model/util/dao/protocoldao.cpp
    model/util/dao/subjectdao.cpp
    model/util/exporterModel/exporter.cpp
    model/util/exporterModel/exporter2d.cpp
    model/util/exporterModel/exporter3d.cpp
    model/util/log/log.cpp
    model/util/readerModel/imagereader.cpp
    model/util/readerModel/reader.cpp
    model/util/readerModel/videoreader.cpp
    view/component/imagelabel.cpp
    view/component/navwidget.cpp
    view/component/selectdeselectwidget.cpp
    view/component/resultmessagewidget.cpp
    view/component/toolbar.cpp
    view/dialog/analysisdialog.cpp
    view/dialog/dialog.cpp
    view/dialog/featureparams.cpp
    view/window/analysisview.cpp
    view/window/apanel.cpp
    view/window/datasetsview.cpp
    view/window/detailedresult.cpp
    view/window/groupview.cpp
    view/window/mainwindow.cpp
    view/window/newdatasetview.cpp
    view/window/newgroupview.cpp
    view/window/newprotocolview.cpp
    view/window/newsubjectview.cpp
    view/window/protocolsview.cpp
    view/window/resultsview.cpp
    view/window/subjectsview.cpp
    view/window/welcomeview.cpp
    model/core/algorithm/fuzzycmeansalgorithm.cpp
    model/core/algorithm/kmeansalgorithm.cpp
    model/core/algorithm/clusterpoint.cpp
    model/core/algorithm/clusterpoint2d.cpp
    model/core/algorithm/clusterpoint3d.cpp
    model/core/algorithm/clustercentroid.cpp
    model/core/algorithm/clustercentroid2d.cpp
    model/core/algorithm/clustercentroid3d.cpp
    model/core/algorithm/fuzzycmeans.cpp
    model/core/algorithm/fuzzycmeans3d.cpp
    model/help/assistant.cpp
    model/core/romeoobject.cpp
    model/core/video.cpp)

#ADD QRC FILES
QT5_ADD_RESOURCES(RESOURCES img/images.qrc style/style.qrc)

#HIDE THE COMMAND PROMPT IN WINDOWS
IF(MINGW)
    ADD_EXECUTABLE(Romeo WIN32 ${headers} ${sources} ${RESOURCES} ${ICON} my.rc)
ELSE()
    ADD_EXECUTABLE(Romeo ${headers} ${sources} ${RESOURCES} ${ICON} my.rc)
ENDIF()


QT5_USE_MODULES(Romeo Widgets Core Gui Sql)

TARGET_LINK_LIBRARIES(Romeo ${Qt5_LIBRARIES} ${ITK_LIBRARIES} ${OpenCV_LIBS})

