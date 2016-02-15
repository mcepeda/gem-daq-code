#ifndef ROOT_CosmicStandEvent
#define ROOT_CosmicStandEvent

//////////////////////////////////////////////////////////////////////////
//                                                                      //
// CosmicStandEvent                                                     //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#include "TObject.h"
#include "TClonesArray.h"
#include "TRefArray.h"
#include "TRef.h"
#include "TH1.h"
#include "TBits.h"
#include "TMath.h"


//#include "Event.h"

class SingleStrip {
      private:
            int fchannel;            
            int fslot;
            int fchamberType;
            double fheight;
            double fx; 
            double fy;
            double fphi;
            double fr;
            bool fON;
            double fminy;
            double fmaxy;

      public:
            SingleStrip(){}
            SingleStrip(const int &channel_, const int &slot_, const int chamberType_,double height_,bool setON_):
            fchannel(channel_),
            fslot(slot_),
            fchamberType(chamberType_),
            fheight(height_),
            fON(setON_){}
            
            ~SingleStrip(){};
            
            void setSingleStripInfo();

            double height(){return fheight;}
            double x(){return fx;}
            double y(){return fy;}
            double z(){return fheight;}
            double phi(){return fphi;}
            double r(){return fr;}      
            bool value(){return fON;}
            int slot(){ return fslot;}
            int ieta(){ return (fslot%8);}
            double miny() {return fminy;}
            double maxy(){ return fmaxy;}

};            

class Chamber {
      private:
            int fchamberType;
            int fposition;
            int fsuperChamber;
            GEBdata fgebData;
            std::string fslotfile;            
            std::vector<SingleStrip> fSingleStrips;
            double fheight;   
            
      public:
            Chamber(){}
            Chamber(const int &chamberType_, const int &position_, const int &superChamber_, GEBdata &gebData_, std::string &slotfile_):
            fchamberType(chamberType_),
            fposition(position_),
            fsuperChamber(superChamber_),
            fgebData(gebData_),
            fslotfile(slotfile_){}

            ~Chamber(){};

            void Build();

            double height() {return fheight;};
            int chamberType () { return fchamberType;}
            int position () { return fposition;}
            double superChamber () { return fsuperChamber;}
            GEBdata gebData () { return fgebData;}                  
            uint16_t ChamberID (){ return fgebData.ChamID(); }
            std::vector<VFATdata> vfats(){ return fgebData.vfats();}
            std::vector<SingleStrip> strips() { return fSingleStrips;}
};

class SuperChamber {
      private:
            int scnumber;
            std::vector<Chamber> scChambers;

      public:
            SuperChamber(){}
            SuperChamber(const int &number_, std::vector<Chamber> &Chambers_):      
            scnumber(number_),
            scChambers(Chambers_){}
            SuperChamber(const int &number_):
            scnumber(number_){}

            ~SuperChamber(){};

            void addChamberData(Chamber &chamber){scChambers.push_back(chamber);};  //make sure they are filled in order... 
            int number() { return scnumber;}
            double height();
            std::vector<Chamber> Chambers()  {return scChambers;}
};

class CosmicStandEvent : public TObject {

    private:
        std::vector<SuperChamber> fSuperChambers; 
        bool fisEventGood;
        int frun;
        int fevent;

    public:
        CosmicStandEvent();
        CosmicStandEvent(int &run_, int &event_):
        frun(run_), fevent(event_){};

        virtual ~CosmicStandEvent();

        void Build(bool isEventGood_);
        void addSuperChamberData(const SuperChamber &superChamber){fSuperChambers.push_back(superChamber);} 
        void Clear();

        std::vector<SuperChamber> SuperChambers(){ return fSuperChambers;}
        bool     isEventGood(){ return fisEventGood;}
        int run(){return frun;}
        int event(){return fevent;}

        ClassDef(CosmicStandEvent,1)               //Event structure
};

#endif
