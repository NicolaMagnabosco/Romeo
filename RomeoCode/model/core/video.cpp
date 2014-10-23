#include "video.h"

using Romeo::Model::Core::Video;
using Romeo::Model::Util::ReaderModel::VideoReader;

VideoReader *Video::reader = new VideoReader();

Video::Video(const QString &name) : fileName(name)
{

}

