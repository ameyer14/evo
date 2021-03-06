//
//  process_vcf_print_routines.cpp
//  vcf_process
//
//  Created by Milan Malinsky on 03/06/2013.
//  Copyright (c) 2013 University of Cambridge. All rights reserved.
//

#include <iostream>
#include "process_vcf_print_routines.h"

// Print a header (helper function used by all the functions below)
void print_header(const std::vector<std::string>& header, std::ofstream& outFile) {
    for (int i = 0; i < header.size(); i++) {
        if (i == (header.size()-1))
            outFile << header[i] << std::endl;
        else 
            outFile << header[i] << "\t";
    }
}

// Printing doubletons
void print_doubleton_distribution(const string& fileRoot, const std::vector<std::string>& header, std::vector<std::vector<int> >& doubletons) {
    rearrange_doubletons(doubletons);
    std::ios_base::openmode mode_out = std::ios_base::out;
    string doubletonFileName = fileRoot + ".doubletons.txt";
    std::ofstream* pDoubletonOutFile = new std::ofstream(doubletonFileName.c_str(), mode_out);
    *pDoubletonOutFile << "# Doubleton distribution:" << fileRoot << ".vcf" << std::endl;
    *pDoubletonOutFile << "# Input file:" << fileRoot << ".vcf" << std::endl;
    
    
    // Print a header
    print_header(header,*pDoubletonOutFile);
    
    // Print the doubletons matrix
    print_matrix<std::vector<std::vector<int> >&>(doubletons, *pDoubletonOutFile);
    
}

// Printing het counts
void print_het_counts(const string& fileRoot, const std::vector<std::string>& header, const std::vector<int>& hetCounts) {
    std::ios_base::openmode mode_out = std::ios_base::out;
    string hetFileName = fileRoot + ".hets.txt";
    std::ofstream* pHetsOutFile = new std::ofstream(hetFileName.c_str(), mode_out);
    *pHetsOutFile << "# Het counts" << std::endl;
    *pHetsOutFile << "# Input file:" << fileRoot << ".vcf" << std::endl;
    
    // print a header
    print_header(header,*pHetsOutFile);

    // print het counts
    for (int i = 0; i < hetCounts.size(); i++) {
        if (i == (hetCounts.size()-1))
            *pHetsOutFile << hetCounts[i] << std::endl;
        else 
            *pHetsOutFile << hetCounts[i] << "\t";
    } 
}


// Printing pairwise difference statistics
void print_pairwise_diff_stats(const string& fileRoot, const std::vector<std::string>& header, const int totalVariantNumber, const std::vector<std::vector<double> >& diffMatrix, const std::vector<std::vector<double> >& diffMatrixMe, const std::vector<std::vector<double> >& diffMatrixHetsVsHomDiff) {
    std::ios_base::openmode mode_out = std::ios_base::out;
    string diffFileName = fileRoot + ".diff_matrix.txt";
    string diffMeFileName = fileRoot + ".diff_me_matrix.txt";
    string hetHomFileName = fileRoot + ".hets_over_homs_matrix.txt";
    std::ofstream* pDiffOutFile = new std::ofstream(diffFileName.c_str(), mode_out);
    std::ofstream* pDiffMeOutFile = new std::ofstream(diffMeFileName.c_str(), mode_out);
    std::ofstream* pHetHomOutFile = new std::ofstream(hetHomFileName.c_str(), mode_out);
    *pDiffOutFile << "# Input file:" << fileRoot << ".vcf" << std::endl;
    *pDiffOutFile << "# Total number of segragating variant sites in this sample:" << totalVariantNumber << std::endl;
    *pDiffOutFile << "# Richard's scoring scheme" << std::endl;
    *pDiffMeOutFile << "# Input file:" << fileRoot << ".vcf" << std::endl;
    *pDiffMeOutFile << "# Total number of segragating variant sites in this sample: " << totalVariantNumber << std::endl;
    *pDiffMeOutFile << "# Homozygous difference = 2, one homozygous, another heterozygous = 1:" << totalVariantNumber << std::endl;
    *pHetHomOutFile << "# Input file:" << fileRoot << ".vcf" << std::endl;
    *pHetHomOutFile << "# number of sites both individuals hets/number of sites individuals have a homozygous difference; i.e. num(1/0::1/0)/num(1/1::0/0)" << std::endl;
    *pHetHomOutFile << "# For a free mixing population, we expect this number ~2; for fully separated species ~0" << std::endl;
    
    // print headers
    print_header(header,*pDiffOutFile);
    print_header(header,*pDiffMeOutFile);
    print_header(header,*pHetHomOutFile);
    
    // print statistics
    print_matrix<const std::vector<std::vector<double> >&>(diffMatrix, *pDiffOutFile);
    print_matrix<const std::vector<std::vector<double> >&>(diffMatrixMe, *pDiffMeOutFile);
    print_matrix<const std::vector<std::vector<double> >&>(diffMatrixHetsVsHomDiff, *pHetHomOutFile);
    
}

// Printing haplotype pairwise difference statistics
void print_H1_pairwise_diff_stats(const string& fileRoot, std::vector<std::string>& header, const int totalVariantNumber, const std::vector<std::vector<double> >& diffMatrixH1) {
    std::ios_base::openmode mode_out = std::ios_base::out;
    string diffFileNameH1 = fileRoot + ".diff_matrix_H1.txt";
    std::ofstream* pDiffH1OutFile = new std::ofstream(diffFileNameH1.c_str(), mode_out);
    *pDiffH1OutFile << "# Input file:" << fileRoot << ".vcf" << std::endl;
    *pDiffH1OutFile << "# Total number of segragating variant sites in this sample:" << totalVariantNumber << std::endl;
    *pDiffH1OutFile << "# Differences between H1 haplotypes:" << std::endl;

    for (std::vector<std::string>::size_type i = 0; i < header.size(); i++) {
        header[i] = header[i] + "_H1";
    }
    
    // print headers
    print_header(header,*pDiffH1OutFile);

    
    // print statistics
    print_matrix<const std::vector<std::vector<double> >&>(diffMatrixH1, *pDiffH1OutFile);
    
}

// Printing haplotype pairwise difference statistics
void print_AllH_pairwise_diff_stats(const string& fileRoot, const std::vector<std::string>& samples, const int totalVariantNumber, const std::vector<std::vector<double> >& diffMatrixAllH) {
    std::ios_base::openmode mode_out = std::ios_base::out;
    string diffFileNameAllH = fileRoot + ".diff_matrix_AllH.txt";
    std::ofstream* pDiffAllHOutFile = new std::ofstream(diffFileNameAllH.c_str(), mode_out);
    *pDiffAllHOutFile << "# Input file:" << fileRoot << ".vcf" << std::endl;
    *pDiffAllHOutFile << "# Total number of segragating variant sites in this sample:" << totalVariantNumber << std::endl;
    *pDiffAllHOutFile << "# Differences between all haplotypes:" << std::endl;
    
    std::vector<std::string> header;
    for (std::vector<std::string>::size_type i = 0; i < samples.size(); i++) {
        header.push_back(samples[i] + "_H1");
        header.push_back(samples[i] + "_H2");
    }
    
    // print headers
    print_header(header,*pDiffAllHOutFile);
    
    
    // print statistics
    print_matrix<const std::vector<std::vector<double> >&>(diffMatrixAllH, *pDiffAllHOutFile);
    
}



