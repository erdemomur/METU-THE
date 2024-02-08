#include "CENGFlight.h"
#include <iostream>

//=======================//
// Implemented Functions //
//=======================//
void CENGFlight::PrintCanNotHalt(const std::string& airportFrom,
                                 const std::string& airportTo,
                                 const std::string& airlineName)
{
    std::cout << "A flight path between \""
              << airportFrom << "\" and \""
              << airportTo << "\" via "
              << airlineName
              << " airlines is not found and cannot be halted"
              << std::endl;
}

void CENGFlight::PrintCanNotResumeFlight(const std::string& airportFrom,
                                         const std::string& airportTo,
                                         const std::string& airlineName)
{
    std::cout << "A flight path between \""
              << airportFrom << "\" and \""
              << airportTo << "\" via "
              << airlineName
              << " airlines cannot be resumed"
              << std::endl;
}

void CENGFlight::PrintFlightFoundInCache(const std::string& airportFrom,
                                         const std::string& airportTo,
                                         bool isCostWeighted)
{
    std::cout << "A flight path between \""
              << airportFrom << "\" and \""
              << airportTo << "\" using "
              << ((isCostWeighted) ? "cost" : "price")
              <<  " is found in cache." << std::endl;
}

void CENGFlight::PrintFlightCalculated(const std::string& airportFrom,
                                       const std::string& airportTo,
                                       bool isCostWeighted)
{
    std::cout << "A flight path is calculated between \""
              << airportFrom << "\" and \""
              << airportTo << "\" using "
              << ((isCostWeighted) ? "cost" : "price")
              <<  "." << std::endl;
}

void CENGFlight::PrintPathDontExist(const std::string& airportFrom,
                                    const std::string& airportTo)
{
    std::cout << "A flight path does not exists between \""
              << airportFrom << "\" and \""
              << airportTo <<"\"." << std::endl;
}

void CENGFlight::PrintSisterAirlinesDontCover(const std::string& airportFrom)
{
    std::cout << "Could not able to generate sister airline list from \""
              << airportFrom <<"\"." << std::endl;
}

void CENGFlight::PrintMap()
{
    navigationMap.PrintEntireGraph();
}

void CENGFlight::PrintCache()
{
    lruTable.PrintTable();
}

CENGFlight::CENGFlight(const std::string& flightMapPath)
    : navigationMap(flightMapPath)
{}

//=======================//
//          TODO         //
//=======================//
void CENGFlight::HaltFlight(const std::string& airportFrom,
                            const std::string& airportTo,
                            const std::string& airlineName)
{
    /* TODO */
    std::vector<GraphVertex> navigationMap22 = navigationMap.getVertexList(); 
    for (GraphVertex airport : navigationMap22){
        if (airport.name == airportFrom){
            for (GraphEdge airline : airport.edges){
                if(navigationMap22[airline.endVertexIndex].name == airportTo && airline.name == airlineName){
                    
                    HaltedFlight haltedFlightInfo;
                    haltedFlightInfo.airportFrom = airportFrom;
                    haltedFlightInfo.airportTo = airportTo;
                    haltedFlightInfo.airline = airlineName;
                    haltedFlightInfo.w0 = airline.weight[0];
                    haltedFlightInfo.w1 = airline.weight[1];

                    haltedFlights.push_back(haltedFlightInfo);

                    navigationMap.RemoveEdge(airlineName,airportFrom,airportTo);
                    
                    return;
                }
            }
        }    
    }
    PrintCanNotHalt(airportFrom,airportTo,airlineName);
}

    // (Direct Function call)
void CENGFlight::ContinueFlight(const std::string& airportFrom,
                                const std::string& airportTo,
                                const std::string& airlineName)
{
    /* TODO */
    
    for (int i=0 ; i<haltedFlights.size(); i++){
        if (haltedFlights[i].airportFrom == airportFrom && 
            haltedFlights[i].airportTo == airportTo &&
            haltedFlights[i].airline == airlineName){
                navigationMap.AddEdge(airlineName,airportFrom,airportTo,haltedFlights[i].w0,haltedFlights[i].w1);
                haltedFlights.erase(haltedFlights.begin()+i);
                return;
            }
    }
    PrintCanNotResumeFlight(airportFrom,airportTo,airlineName);
}

void CENGFlight::FindFlight(const std::string& startAirportName,
                            const std::string& endAirportName,
                            float alpha)
{
    /* TODO */
    
    std::vector<GraphVertex> airportList = navigationMap.getVertexList();

    int startInt = navigationMap.getVertexIndex(startAirportName);
    int endInt   = navigationMap.getVertexIndex(endAirportName);
    
    if (startInt==-1 || endInt==-1) return;
    
    std::vector<int> orderedVertexEdgeIndexList;
    std::vector<int> intArray;
    
    bool isCosted = false;

    if (alpha == 0) isCosted = true;
    if (lruTable.Find(intArray,startInt,endInt,isCosted,isCosted)){
        PrintFlightFoundInCache(startAirportName,endAirportName,isCosted);
        navigationMap.PrintPath(intArray, alpha, true);
    }
    else{
        bool pathExists = navigationMap.HeuristicShortestPath(orderedVertexEdgeIndexList, startAirportName, endAirportName, alpha);
        if (pathExists){
            if(alpha==0 || alpha ==1){
            lruTable.Insert(orderedVertexEdgeIndexList, isCosted);
            PrintFlightCalculated(startAirportName, endAirportName, isCosted);
        }
            navigationMap.PrintPath(orderedVertexEdgeIndexList, alpha, true);
        }
        else{
            PrintPathDontExist(startAirportName, endAirportName);
        }
    }
    
}

void CENGFlight::FindSpecificFlight(const std::string& startAirportName,
                                    const std::string& endAirportName,
                                    float alpha,
                                    const std::vector<std::string>& unwantedAirlineNames) const
{
    /* TODO */
    std::vector<GraphVertex> airportList = navigationMap.getVertexList();

    int startInt = navigationMap.getVertexIndex(startAirportName);
    int endInt   = navigationMap.getVertexIndex(endAirportName);
    
    if (startInt==-1 || endInt==-1) return;
    
    std::vector<int> orderedVertexEdgeIndexList;
    std::vector<int> intArray;
    
    bool isCosted = false;

    if (alpha == 0) isCosted = true;
    
    bool pathExists = navigationMap.FilteredShortestPath(orderedVertexEdgeIndexList, startAirportName, endAirportName, alpha,unwantedAirlineNames);
    if (pathExists){
        //std::cout << orderedVertexEdgeIndexList.size();
        navigationMap.PrintPath(orderedVertexEdgeIndexList, alpha, true);
    }
    else{
        PrintPathDontExist(startAirportName, endAirportName);
    }
}

void CENGFlight::FindSisterAirlines(std::vector<std::string>& airlineNames,
                               const std::string& startAirlineName,
                               const std::string& airportName) const
{
    /* TODO */
}

int CENGFlight::FurthestTransferViaAirline(const std::string& airportName,
                                           const std::string& airlineName) const
{
    /* TODO */
    std::vector<GraphVertex> airportList = navigationMap.getVertexList();
    int varMi=0;
    for (GraphVertex wanted : airportList){
        if (wanted.name == airportName) varMi=1;
    }
    if (!varMi) return -1;
    
    int a = navigationMap.MaxDepthViaEdgeName(airportName,airlineName);
    if (a>=0) return a;

}