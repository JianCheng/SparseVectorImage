/*=========================================================================
 
 Program:   Sparse Vector Image File Writer
 
 Copyright (c) Pew-Thian Yap. All rights reserved.
 See http://www.unc.edu/~ptyap/ for details.
 
 This software is distributed WITHOUT ANY WARRANTY; without even
 the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 PURPOSE.  See the above copyright notices for more information.
 
 =========================================================================*/

#ifndef __itkSparseVectorImageFileWriter_h
#define __itkSparseVectorImageFileWriter_h

#include "itkProcessObject.h"
#include "itkExceptionObject.h"
#include "itkImage.h"
#include "itkImageFileWriter.h"

namespace itk
{

/** \class SparseVectorImageFileWriter
 * \brief Writes sparse vector image data to key and value files.
 *
 */
template <class TInputImage>
class ITK_EXPORT SparseVectorImageFileWriter : public ProcessObject
{
public:
  /** Standard class typedefs. */
  typedef SparseVectorImageFileWriter     Self;
  typedef ProcessObject             Superclass;
  typedef SmartPointer<Self>        Pointer;
  typedef SmartPointer<const Self>  ConstPointer;

  /** Method for creation through the object factory. */
  itkNewMacro(Self);

  /** Run-time type information (and related methods). */
  itkTypeMacro(SparseVectorImageFileWriter,ProcessObject);

  /** Some convenient typedefs. */
  typedef TInputImage                                            InputImageType;
  typedef typename InputImageType::Pointer                       InputImagePointer;
  typedef typename InputImageType::RegionType                    InputImageRegionType; 
  typedef typename InputImageType::SizeType                      InputImageSizeType; 
  typedef typename InputImageType::SpacingType                   InputImageSpacingType; 
  typedef typename InputImageType::InternalPixelType             InputImagePixelType;
  typedef typename InputImageType::ValueType                     InputImageValueType;
  typedef typename InputImageType::PixelContainer                InputImagePixelContainerType;  
  typedef typename InputImageType::PixelContainer::Pointer       InputImagePixelContainerPointerType;  
  typedef typename InputImageType::PixelContainer::PixelMapType  InputImagePixelMapType;
  typedef typename InputImagePixelMapType::iterator              InputImagePixelMapIteratorType;
  
  /** Set/Get the image input of this writer.  */
  using Superclass::SetInput;
  void SetInput(const InputImageType *input);
  const InputImageType * GetInput(void);
  const InputImageType * GetInput(unsigned int idx);
  
  /** Specify the names of the output files to write. */
  itkSetStringMacro(FileName);
  itkGetStringMacro(FileName);
  
  /** A special version of the Update() method for writers.  It
   * invokes start and end events and handles releasing data. It
   * eventually calls GenerateData() which does the actual writing.
   * Note: the write method will write data specified by the
   * IORegion. If not set, then then the whole image is written.  Note
   * that the region will be cropped to fit the input image's
   * LargestPossibleRegion. */
  virtual void Write(void);

  /** Aliased to the Write() method to be consistent with the rest of the
   * pipeline. */
  virtual void Update()
    {
    this->Write();
    }

  /** Set the compression On or Off */
  itkSetMacro(UseCompression,bool);
  itkGetConstReferenceMacro(UseCompression,bool);
  itkBooleanMacro(UseCompression);

  /** By default the MetaDataDictionary is taken from the input image and 
   *  passed to the ImageIO. In some cases, however, a user may prefer to 
   *  introduce her/his own MetaDataDictionary. This is often the case of
   *  the ImageSeriesWriter. This flag defined whether the MetaDataDictionary 
   *  to use will be the one from the input image or the one already set in
   *  the ImageIO object. */
//  itkSetMacro(UseInputMetaDataDictionary,bool);
//  itkGetConstReferenceMacro(UseInputMetaDataDictionary,bool);
//  itkBooleanMacro(UseInputMetaDataDictionary);


protected:
  SparseVectorImageFileWriter();
  ~SparseVectorImageFileWriter();
  void PrintSelf(std::ostream& os, Indent indent) const;

  typedef unsigned long KeyType;
  typedef Image<KeyType, 1> KeyImageType;
  typedef Image<InputImagePixelType, 1> ValueImageType;
  typedef typename KeyImageType::Pointer KeyImagePointer;
  typedef typename ValueImageType::Pointer ValueImagePointer;
    
  KeyImagePointer KeyImage;
  ValueImagePointer ValueImage;

  typedef itk::ImageFileWriter<KeyImageType> KeyImageFileWriterType;
  typedef itk::ImageFileWriter<ValueImageType> ValueImageFileWriterType;
  
  typename KeyImageFileWriterType::Pointer KeyImageFileWriter;
  typename ValueImageFileWriterType::Pointer ValueImageFileWriter;
  
  /** Does the actual work. */
  void GenerateData(void);

  
private:
  SparseVectorImageFileWriter(const Self&); //purposely not implemented
  void operator=(const Self&); //purposely not implemented

  std::string        m_FileName;
  
  bool m_UseCompression;
//  bool m_UseInputMetaDataDictionary;        // whether to use the
                                            // MetaDataDictionary from the
                                            // input or not.  
};

  
} // end namespace itk
  
#ifndef ITK_MANUAL_INSTANTIATION
#include "itkSparseVectorImageFileWriter.hxx"
#endif

#endif // __itkSparseVectorImageFileWriter_h
