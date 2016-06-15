
#ifdef _WIN32
#define __GNU_LIBRARY__
#endif

#ifdef _WIN32
#pragma warning( disable : 4291 ) // Disable VC warning messages for
                                  // new(nothrow)
#endif


#include <iostream>
#include <fstream>
#include <time.h>
#include "PvmProjector.h"
#include "CLineProgress.h"
#include "ProjUtil.h"
#include "inparms.h"
#include "PvmProjectorSlave.h"
using namespace ProjLib;


int main(int argc, char *argv[])
{
  PvmProjector projector;        //if this the master then use this
  PvmProjectorSlave slave;       //if this is the slave then use this
  CLineProgress progress;        //progress for command line output
  clock_t start = 0, finish = 0; //for time files
  std::ofstream out;             //for output time files
  Projection * outproj = NULL;   //output projection
  inputparm inparms;             //for master setup and parameters

  try
  {
    if (argc == 1)
    {
      //we are the master with out a flat file so get input
      inparms.getinput();
    }
    else
    {
      //check to see if the slave flag has been passed to the project file
      if (std::string(argv[1]) == std::string("-s"))
      {
        slave.connect();  //connnect to the master and go
        return 0;
      }
      else //we are the master and it is flat file
      {
        if (!inparms.read_parm_file(argv[1]))
        {
           std::cout << "Unable to read the configuration file" << std::endl;
           return 0;
        }
      }
    }

    //generate the output projection based on the flat file
    outproj = SetProjection(inparms.parameterfile);
    if (!outproj)
    {
      std::cout << "Could not create the output projection!" << std::endl;
      return 0;
    }
    
    //check for the time file
    if (inparms.timefile)
    {
      out.open(inparms.logname.c_str()); //open the ouput file
      start = time(NULL);                //get the start
      out << start << std::endl;         //output the start
    }
    projector.setOutputFileName(inparms.outfile_name);
    projector.setOutputProjection(outproj);
    projector.setPmeshName(inparms.pmeshname);
    projector.setPmeshSize(inparms.pmeshsize);
    if (inparms.chunksize > 0)
      projector.setChunkSize(inparms.chunksize);
    else
      projector.setChunkSize(1);

    projector.setSlaveStoreLocal(inparms.storelocal);

    projector.setStitcher(inparms.stitcher);

    if (!inparms.samescale)
      projector.setOutputScale(inparms.newscale);
    else
      projector.setSameScale(true);
    
    projector.setInputFile(inparms.filename);
    projector.setNumberOfSlaves(inparms.numofslaves);
    projector.project(&progress);

    //see if we need to write the time file
    if (inparms.timefile)
    {
      finish = time(NULL);
      out << finish << std::endl;
      out << (finish - start);
      out.close();
    }
  }
  catch(ProjectorException & pe)
  {
    std::cout << pe.getExceptionMessage() << std::endl;
  }
  catch(USGSImageLib::ImageException &  ie)
  {
    std::string error;

    ie.getString(error);
    std::cout << error << std::endl;
  }
  catch(...)
  {
    std::cout << "An exception has been thrown" << std::endl;
  }

  return 0;  //done

}










