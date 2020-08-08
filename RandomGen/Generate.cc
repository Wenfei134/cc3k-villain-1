#include "../Floor.h"
#include "RandomGeneration.h"
#include "RandomEnemy.h"
#include "RandomPotion.h"
#include "RandomGold.h"
#include "../Info.h"
#include "../Ground.h"
#include "../Tile.h"
#include "../Characters/Player.h"
#include "../Enemies/Enemy.h"
#include "../Items/Gold.h"
#include "../Items/Potion.h"
#include "../Items/DragonGold.h"
#include <vector>
#include <memory>

using namespace std;

void Floor::getChamber(int & chamIndex, RandomGeneration & rng, int & NUM_CHAMBERS, const int player ) {
    chamIndex = rng.randomInt( NUM_CHAMBERS );
    while( chamIndex == player ){
        chamIndex = rng.randomInt( NUM_CHAMBERS );
    }
}

std::shared_ptr<Ground> Floor::generateLocation( int & chamIndex, int & tileIndex, vector<vector<shared_ptr<Ground> > > & chambers, 
    RandomGeneration & rng, int & NUM_CHAMBERS, const int player ){
    
    getChamber( chamIndex, rng, NUM_CHAMBERS, player );

    int NUM_TILES = chambers[chamIndex].size(); 
    while( NUM_TILES == 0 ){
        if( chamIndex == 0 ){
            chambers.erase( chambers.begin() );
        } else {
            chambers.erase( chambers.begin() + chamIndex );
        }
        NUM_CHAMBERS--;
        getChamber( chamIndex, rng, NUM_CHAMBERS, player );
        NUM_TILES = chambers[chamIndex].size(); 
    }

    tileIndex = rng.randomInt( NUM_TILES );

    return chambers[chamIndex][tileIndex];
}

void Floor::removeTile( int & chamIndex, int & tileIndex, vector<vector<shared_ptr<Ground> > > & chambers){
    if( tileIndex == 0 ){
        chambers[chamIndex].erase( chambers[chamIndex].begin() );
    } else{
        chambers[chamIndex].erase( chambers[chamIndex].begin() + tileIndex );
    }
}

void Floor::generate( std::shared_ptr<Player> p ){
    int NUM_CHAMBER = 5;
    int NUM_ENEMIES = 20;
    int NUM_POTIONS = 10;
    int NUM_GOLD = 10;
    int chamIndex, tileIndex;
    vector<vector<shared_ptr<Ground> > > chambers;

    for( int i = 0; i < NUM_CHAMBER; i++){
        vector<shared_ptr<Ground> > chamber;
        chambers.push_back( chamber );
    }

    for( int i = 0; i < NUM_CHAMBER; i ++) { //this adds all the ground floors to their respective chamber vector
        for(auto r : tiles ){
            for( auto tile : r ){
                if( tile->type == State::Ground ){
                    auto ground = static_pointer_cast< Ground >( tile );
                    if( ground->chamber == i ){
                        chambers[i].push_back( ground );
                    }
                }
            }
        }
    }

    RandomGeneration rng = RandomGeneration();
    rng.setSeed();

    auto playerTile = generateLocation( chamIndex, tileIndex, chambers, rng, NUM_CHAMBER );
    playerTile->setPlayer( p );
    p->setLocation( playerTile );
    removeTile( chamIndex, tileIndex, chambers );
    
    auto stairTile = generateLocation( chamIndex, tileIndex, chambers, rng, NUM_CHAMBER, chamIndex );
    stairTile->setStair( true );
    removeTile( chamIndex, tileIndex, chambers );

    int toSpawn = NUM_POTIONS + NUM_GOLD + NUM_ENEMIES;
    NUM_GOLD += NUM_POTIONS;
    NUM_ENEMIES += NUM_GOLD;

    int RH = 1; 
    int BA = 1; 
    int BD = 1; 
    int PH = 1; 
    int WA = 1; 
    int WD = 1; 
    RandomPotion rpg = RandomPotion( RH, BA, BD, PH, WA, WD);
    rpg.setSeed();
    int small = 2; 
    int dragon = 1; 
    int normal = 5; 
    RandomGold rgg = RandomGold( small, dragon, normal );
    rgg.setSeed();
    int H = 4; 
    int W = 3; 
    int E = 5; 
    int O = 2; 
    int M = 2; 
    int L = 2; 
    RandomEnemy reg = RandomEnemy( H, W, E, O, M, L);
    reg.setSeed();

    for( int i = 0; i < toSpawn; i++ ){
        auto tile = generateLocation( chamIndex, tileIndex, chambers, rng, NUM_CHAMBER );
        if( i >  NUM_GOLD){
            auto enemy = reg.get();
            tile->setEnemy( enemy );
        }
        if( i >  NUM_POTIONS){
            auto gold = rgg.get();
            auto dg = dynamic_pointer_cast< DragonGold> (gold);
            if( dg != nullptr ){
                randomDragon( dg, tile );
            }
            tile->setGold( gold );
        }
        else{
            auto potion = rpg.get();
            tile->setPotion( potion );
        }
        removeTile( chamIndex, tileIndex, chambers );
    }
}
