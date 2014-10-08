// -*- c-basic-offset: 2 -*-

/* Copyright (c) 2014, EPFL/Blue Brain Project
 *                     Stefan.Eilemann@epfl.ch
 */
#ifndef FIVOX_IMAGESOURCE_H
#define FIVOX_IMAGESOURCE_H

#pragma GCC diagnostic ignored "-Wsign-promo"
#ifdef LB_GCC_4_6_OR_LATER
#  pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#endif
#ifdef final
#  undef final
#endif

#include <itkImageSource.h>


namespace fivox
{
/** Image source filter using a functor on each pixel to generate the output */
template< typename TImage, typename TFunctor >
class ImageSource : public itk::ImageSource< TImage >
{
public:
  /** Standard class typedefs. */
  typedef ImageSource                              Self;
  typedef itk::ImageSource< TImage >               Superclass;
  typedef itk::SmartPointer< Self >                Pointer;
  typedef itk::SmartPointer< const Self >          ConstPointer;

  /** Method for creation through the object factory. */
  itkNewMacro(Self);

  /** Run-time type information (and related methods). */
  itkTypeMacro(ImageSource, itk::ImageSource);

  /** Typedef to describe the output image region types. */
  typedef TImage                          ImageType;
  typedef typename ImageType::RegionType  ImageRegionType;

  typedef typename ImageType::Pointer      ImagePointer;
  typedef typename ImageType::ConstPointer ImageConstPointer;

  /** Typedef to describe the type of pixel. */
  typedef typename ImageType::PixelType ImagePixelType;

  /** Typedef to describe the output and input image index and size types. */
  typedef typename ImageType::IndexType ImageIndexType;
  typedef typename ImageType::SizeType  ImageSizeType;

  /** ImageDimension enumeration */
  itkStaticConstMacro(ImageDimension, unsigned int, ImageType::ImageDimension);

  /** @return the functor executed for each pixel during update. */
  itkGetMacro(Functor, TFunctor&);
  itkGetConstMacro(Functor, const TFunctor&);

protected:
  ImageSource();
  ~ImageSource() {}

  void PrintSelf(std::ostream & os, itk::Indent indent) const;

  /** ImageSource is implemented as a multithreaded filter. */
  void ThreadedGenerateData(const ImageRegionType& outputRegionForThread,
                            itk::ThreadIdType threadId);

private:
  ImageSource(const Self &); //purposely not implemented
  void operator=(const Self &);   //purposely not implemented

  TFunctor m_Functor;
};
} // end namespace fivox

#  ifndef ITK_MANUAL_INSTANTIATION
#    include "imageSource.hxx"
#  endif
#endif