//======== Copyright (c) 2022, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     White Box - test suite
//
// $NoKeywords: $ivs_project_1 $white_box_tests.cpp
// $Author:     MAREK SUCHARDA <xsucha18@stud.fit.vutbr.cz>
// $Date:       $2023-03-07
//============================================================================//
/**
 * @file white_box_tests.cpp
 * @author MAREK SUCHARDA
 * 
 * @brief Implementace testu hasovaci tabulky.
 */

#include <vector>

#include "gtest/gtest.h"

#include "white_box_code.h"

//============================================================================//
// ** ZDE DOPLNTE TESTY **
//
// Zde doplnte testy hasovaci tabulky, testujte nasledujici:
// 1. Verejne rozhrani hasovaci tabulky
//     - Vsechny funkce z white_box_code.h
//     - Chovani techto metod testuje pro prazdnou i neprazdnou tabulku.
// 2. Chovani tabulky v hranicnich pripadech
//     - Otestujte chovani pri kolizich ruznych klicu se stejnym hashem 
//     - Otestujte chovani pri kolizich hashu namapovane na stejne misto v 
//       indexu
//============================================================================//


class HashTable : public ::testing::Test
{
protected:
    
}; 

TEST_F(HashTable, EmptyTable)
{
    // hash_map_state_code_t ht; 
    // auto ht = hash_map_ctor(); 
    // hash_map_t *ht; 
    // EXPECT_EQ(ht->used, 4); 
    // printf("%ld used\n", ht->used); 
    // printf("%lld index \n", ht->index); 

    // auto item = hash_map_get(ht, 'key');
    // printf("%d", item->value); 

    // printf(ht); 
    
    // test na prazdnou tabulku 
    // EXPECT_EQ(ht->size, 0); 
    // EXPECT_EQ(ht->capacity, 0); 
    // EXPECT_EQ(ht->data, nullptr); 
}

hash_map_t *hm; 

// Index hledané položky lze jednoduše získat jako zbytek po dělení haše a velikostí tabulky. 


TEST_F(HashTable, hash_map_ctor) {
    hash_map_t* map = hash_map_ctor(); 
    // 1. nevraci null - neni chyba alokace pameti
    EXPECT_NE(map, nullptr); 
} 

TEST_F(HashTable, hash_map_dtor) {
    hash_map_t* map = hash_map_ctor();
    
    // alokuje se 8 bytu
    EXPECT_EQ(map->allocated, 8); 
    // tady to zmeni na 0 bytu 
    hash_map_dtor(map); 
    EXPECT_EQ(map->allocated, 0); 

}

TEST_F(HashTable, clear) {
    hash_map_t* map = hash_map_ctor(); 
    // nic to nedela proste
    // std::cout << map->allocated << std::endl; 
    // std::cout << map->dummy << std::endl; 
    // std::cout << map->index << std::endl; 
    // std::cout << map->first << std::endl; 
    // std::cout << map->last << std::endl; 
    // std::cout << map->used << std::endl; 
    hash_map_clear(map); 
    // std::cout << map->allocated << std::endl; 
    // std::cout << map->dummy << std::endl; 
    // std::cout << map->index << std::endl; 
    // std::cout << map->first << std::endl; 
    // std::cout << map->last << std::endl; 
    // std::cout << map->used << std::endl; 
    EXPECT_EQ(map->allocated, 8); 
} 

TEST_F(HashTable, hash_map_reserve) {
    hash_map_t* map = hash_map_ctor();
    EXPECT_TRUE(hash_map_capacity(map) == 8); 

    hash_map_reserve(map, 16);
    EXPECT_TRUE(hash_map_capacity(map) == 16); 
    
} 

TEST_F(HashTable, hash_map_size) {
    hash_map_t* map = hash_map_ctor(); 

    // nova tabulka bude prazdna
    EXPECT_EQ(hash_map_size(map), 0); 
    
    // pridam 2 prvky, ocekavam eq 2
    hash_map_put(map, "key", 10); 
    hash_map_put(map, "key2", 20); 
    
    EXPECT_EQ(hash_map_size(map), 2); 
    
    // std::cout << hash_map_capacity(map) << std::endl; 
}

TEST_F(HashTable, hash_map_capacity) {
    hash_map_t* map = hash_map_ctor(); 

    // nova tabulka bude prazdna
    EXPECT_EQ(hash_map_capacity(map), 8); 

    // std::cout << hash_map_capacity(map) << std::endl;
    // std::cout << map->allocated << std::endl;

    hash_map_capacity(map); 

    hash_map_put(map, "key", 10); 

    hash_map_capacity(map); 

    // std::cout << hash_map_capacity(map) << std::endl;
    // std::cout << map->allocated << std::endl; 

    // nemeni se alokace
}

TEST_F(HashTable, hash_map_contains) {
    hash_map_t* map = hash_map_ctor(); 
    // zadny klic tam neni
    EXPECT_FALSE(hash_map_contains(map, "key")); 
    // vlozim klic, ocekavam, ze ho to najde
    hash_map_put(map, "key", 10); 
    EXPECT_TRUE(hash_map_contains(map, "key")); 
}

TEST_F(HashTable, hash_map_put) {
    hash_map_t* map = hash_map_ctor(); 

    // to je slozite

} 

TEST_F(HashTable, hash_map_get) {
    hash_map_t* map = hash_map_ctor(); 

    int value; 
    hash_map_get(map, "key", &value); 


    // std::cout << hash_map_contains(map, "key") << std::endl;
    // hash_map_put(map, "key", 10); 
    // std::cout << hash_map_contains(map, "key") << std::endl; 
    // std::cout << hash_map_size(map) << std::endl; 
    // std::cout << hash_map_get(map, "key", &value) << std::endl; 
    // taky nevim:{
} 






/*** Konec souboru white_box_tests.cpp ***/
