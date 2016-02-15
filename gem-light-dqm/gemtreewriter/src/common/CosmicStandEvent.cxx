#include "TRandom3.h"
#include "gem/readout/GEMDataAMCformat.h"
#include "gem/datachecker/GEMDataChecker.h"
#include "GEMClusterization/GEMStrip.h"
#include "GEMClusterization/GEMStripCollection.h"

#include <memory>
#include <map>

#include "RVersion.h"
#include "TRandom.h"
#include "TDirectory.h"
#include "TProcessID.h"

#include "Event.h"
#include "CosmicStandEvent.h"

#include "ChamberMeasurements.h"

ClassImp(CosmicStandEvent);

void SingleStrip::setSingleStripInfo(){
        //Dummy while I work this out

        int ieta=(fslot%8);

        double ycenter=(LC_ShortEdgeH_EtaPartition[ieta]+LC_LongEdgeH_EtaPartition[ieta])/2;
        double vercenter=(LC_LongEdgeB_EtaPartition[0]/LC_FullR)*(ycenter+LC_SmallR);

        double xc=-vercenter/2+vercenter*fchannel/Total_Channels;

        fx=xc;
        fy=ycenter;
        fphi=(fchannel-Total_Channels/2)*LC_angle/Total_Channels; // This is the angle with respect to the radius in the center of the chamber, is that what we want?
                                                                  // Double check the signs!
        fr=sqrt(xc*xc+ycenter*ycenter); 
        fminy=LC_ShortEdgeH_EtaPartition[ieta];
        fmaxy=LC_LongEdgeH_EtaPartition[ieta];

        // Check in radial!

        // Do we need the pitch? 
        // It would be more elegant to write this in terms of  cmssw/Geometry/CommonTopologies/interface/TrapezoidalStripTopology.h

}

void Chamber::Build(){

        fheight=fsuperChamber*Stand_distancebetweenSC+Stand_distancebetweenchambersinoneSC*fposition;


        // This should probably move!! Why do it everytime? 
        // Also it would be better to have 1 file with all the slot configurations (which will depend on the chamber, right
        // now I am assuming they are identical)
        std::unique_ptr<gem::readout::GEMslotContents> slotInfoCS = std::unique_ptr<gem::readout::GEMslotContents> (new gem::readout::GEMslotContents(fslotfile));

        std::map<int,int> strip_maps[24];
        std::string maps[24];

        std::string path = std::getenv("BUILD_HOME");
        for (int im = 0; im < 24; im++){
                if (im < 2) {
                        path += "/gem-light-dqm/dqm-root/data/v2b_schema_chips0-1.csv";
                } else if (im < 16) {
                        path += "/gem-light-dqm/dqm-root/data/v2b_schema_chips2-15.csv";
                } else if (im < 18) {
                        path += "/gem-light-dqm/dqm-root/data/v2b_schema_chips16-17.csv";
                } else {
                        path += "/gem-light-dqm/dqm-root/data/v2b_schema_chips18-23.csv";
                }
                maps[im] = path;
                path= std::getenv("BUILD_HOME");  
        }

        for (uint32_t vfatN=0; vfatN<fgebData.vfats().size(); vfatN++){
                VFATdata vfat=fgebData.vfats().at(vfatN);
                uint16_t  ChipID = (0x0fff & vfat.ChipID());
                int fslot = slotInfoCS->GEBslotIndex(ChipID);
                uint64_t  lsData = vfat.lsData();
                uint64_t  msData = vfat.msData();

                int min=int(fslot/8)*128;


                // This should probably move!! Why do it everytime?   
                std::string ifpath_ = maps[fslot];
                std::ifstream icsvfile_;
                icsvfile_.open(ifpath_);
                if(!icsvfile_.is_open()) {
                        std::cout << "\nThe file: " << icsvfile_ << " is missing.\n" << std::endl;
                        std::cout<<ifpath_<<std::endl;
                        return;
                }
                for (int il = 0; il < 128; il++) {
                        std::string line;
                        std::getline(icsvfile_, line);
                        std::istringstream iss(line);
                        std::pair<int,int> map_;
                        std::string val;
                        std::getline(iss,val,',');
                        std::stringstream convertor(val);
                        convertor >> std::dec >> map_.second;  // I dont understand why do we revert this, but following treeReader for consistency
                        std::getline(iss,val,',');
                        convertor.str("");
                        convertor.clear();
                        convertor << val;
                        convertor >> std::dec >> map_.first;
                        strip_maps[fslot].insert(map_);
                }

                for(int i=0; i<64; i++){
                        bool settrue = (lsData >> i) & 0x1;

                        int strip=127-strip_maps[fslot].find(i+1)->second+min;  // this is how it is done in the treereader?

                        SingleStrip testStrip(strip,fslot,fchamberType,fheight,settrue);                 
                        testStrip.setSingleStripInfo(); 
                        fSingleStrips.push_back(testStrip);
                }

                for(int i=0; i<64; i++){ 
                        bool settrue = (msData >> i) & 0x1;

                        int strip = 127 - strip_maps[fslot].find(i+64+1)->second+min;

                        SingleStrip testStrip(strip,fslot,fchamberType,fheight,settrue);
                        testStrip.setSingleStripInfo(); 
                        fSingleStrips.push_back(testStrip);
                }
        }

}

double SuperChamber::height(){return scnumber*Stand_distancebetweenSC;}


CosmicStandEvent::CosmicStandEvent()
{
        // Create an CosmicStandEvent object.
        Clear();
}

//______________________________________________________________________________
CosmicStandEvent::~CosmicStandEvent()
{
        Clear();
}

//______________________________________________________________________________
void CosmicStandEvent::Build(bool isEventGood_)
{
        //Save current Object count
        Int_t ObjectNumber = TProcessID::GetObjectCount();
        Clear();
        fisEventGood = isEventGood_;

        //Restore Object count 
        //To save space in the table keeping track of all referenced objects
        //we assume that our events do not address each other. We reset the 
        //object count to what it was at the beginning of the event.
        TProcessID::SetObjectCount(ObjectNumber);
}  

/*void CosmicStandEvent::SetHeader(Int_t i, Int_t run, Int_t date)
  {
//   fEvtHdr.Set(i, run, date);
}
*/

//______________________________________________________________________________
void CosmicStandEvent::Clear()
{
        fisEventGood = false;
}





