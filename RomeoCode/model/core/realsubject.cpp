#include "realsubject.h"

using Romeo::Model::Core::RealSubject;

RealSubject::RealSubject() : ISubject(), imageFormat(0)
{

}

RomeoObject *RealSubject::getImageFormat()
{
    return imageFormat;
}

RealSubject::~RealSubject()
{

}
