//======== Copyright (c) 2023, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     Test Driven Development - graph
//
// $NoKeywords: $ivs_project_1 $tdd_code.cpp
// $Author:     MAREK SUCHARDA <xsucha18@stud.fit.vutbr.cz>
// $Date:       $2023-03-07
//============================================================================//
/**
 * @file tdd_code.cpp
 * @author Martin Dočekal
 * @author Karel Ondřej
 *
 * @brief Implementace metod tridy reprezentujici graf.
 */

#include "tdd_code.h"


Graph::Graph(){}

Graph::~Graph(){}

std::vector<Node*> Graph::nodes() {
    std::vector<Node*> nodes;

    for (int i = 0; i < nodes_vector.size(); i++) {
        // std::cout << &nodes_vector << std::endl; 
        nodes.push_back(&nodes_vector[i]); 
        // std::cout << &nodes_vector << std::endl; 
    }

    return nodes;
}

std::vector<Edge> Graph::edges() const {
    std::vector<Edge> edges;
    for (auto edge : edges_vector) {
        // if (!containsEdge(edge)) {
            std::cout << edge << std::endl;
            std::cout << edges.size() << std::endl;
            edges.push_back(edge); 
        // }
    }

    return edges;
   
}

Node* Graph::addNode(size_t nodeId) { 
    // check jestli noda existuje
    for (int i = 0; i < nodes_vector.size(); i++) {
        if (nodes_vector[i].id == nodeId) {
            return nullptr; 
        }
    }

    // vytvorim uzel 
    Node node; 
    node.id = nodeId; 
    // hodim ho do nodes_vector
    nodes_vector.push_back(node); 
    // returnnu posledni prvek
    return &nodes_vector[nodes_vector.size() - 1]; 
}

bool Graph::addEdge(const Edge& edge){

    // ignoruje duplicitni 
    if (containsEdge(edge)) {
        return NULL;
    } else if (edge.a == edge.b) {
        return false;
    } else {
        addNode(edge.a); 
        addNode(edge.b); 
        edges_vector.push_back(edge); 
        return true;
    } 

    return 0; 
}

void Graph::addMultipleEdges(const std::vector<Edge>& edges) {
    for (auto edge : edges) {

        addEdge(edge); 
    }
}

Node* Graph::getNode(size_t nodeId){ 
    for (int i = 0; i < nodeCount(); i++) {
        // kdyz ids matchujou, return ukazatel na uzel s danym id jinak nullptr
        if (nodes_vector[i].id == nodeId) {
            // std::cout << "match" << std::endl; 
            return &nodes_vector[i]; 
        } 
    }

    return nullptr;
}

bool Graph::containsEdge(const Edge& edge) const{
    
    for (int i = 0; i < edges_vector.size(); i++) {
        if (edges_vector[i] == edge) {
            return true; 
        }
    }

    return false;
}

void Graph::removeNode(size_t nodeId){    

    for (int i = 0; i < nodes_vector.size(); i++) {
        std::cout << nodes_vector[i].id << std::endl; 
        if (nodes_vector[i].id == nodeId) {
            nodes_vector.erase(nodes_vector.begin() + i); 
        }
    } 

    throw std::out_of_range("Out of range"); 

}

void Graph::removeEdge(const Edge& edge){ 

    for (int i = 0; i < edges_vector.size(); i++) {
        // std::cout << edges_vector[i] << std::endl; 
        if (edges_vector[i] == edge) {
            edges_vector.erase(edges_vector.begin() + i); 
        }
    }

    throw std::out_of_range("Out of range"); 

    // remove edge from graph


}

size_t Graph::nodeCount() const{

    int i = 0; 
    for (auto node : nodes_vector) {
        i++; 
    } 

    return i; 
}

size_t Graph::edgeCount() const{
    int i = 0; 
    for (auto edge : edges_vector) {
        i++; 
    } 

    return i; 
}

size_t Graph::nodeDegree(size_t nodeId) const{ 

    int i = 0; 
    for (auto edge : edges_vector) {
        if (edge.a == nodeId || edge.b == nodeId) i++;
    } 

    throw std::out_of_range("Out of range"); 

    return i;
}

size_t Graph::graphDegree() const{ 

    int max = 0; 
    for (auto edge : edges_vector) {
        if (edge.a > max) {
            max = edge.a; 
        } else if (edge.b > max) {
            max = edge.b; 
        }
    } 

    return max;
}

void Graph::coloring(){
}

void Graph::clear() { 

    for (auto edge : edges_vector) {
        edges_vector.erase(edges_vector.begin()); 
    } 
    for (auto node : nodes_vector) {
        nodes_vector.erase(nodes_vector.begin()); 
    } 

} 

/*** Konec souboru tdd_code.cpp ***/