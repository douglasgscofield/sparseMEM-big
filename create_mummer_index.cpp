#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

#include "sparseSA.hpp"
#include "fasta.hpp"

#include <getopt.h>
#include <time.h>
#include <sys/time.h>

#include <cctype> // std::tolower(), uppercase/lowercase conversion
#include <boost/archive/binary_oarchive.hpp>

// NOTE use of special characters ~, `, and $ !!!!!!!!

using namespace std;

void usage(string prog);

bool _4column = false;
int K = 1;
sparseSA *sa;


int main(int argc, char* argv[]) {
  while (1) {
    static struct option long_options[] = {
      {"k", 1, 0, 0}, // 0
      {"F", 0, 0, 0}  // 1
    };
    int longindex = -1;
    int c = getopt_long_only(argc, argv, "", long_options, &longindex);
    if(c == -1) break; // Done parsing flags.
    else if(c == '?') { // If the user entered junk, let him know.
      cerr << "Invalid parameters." << endl;
      usage(argv[0]);
    }
    else {
      // Branch on long options.
      switch(longindex) {
      case 0: K = atoi(optarg); break;
      case 1: _4column = true; break;
      default: break;
      }
    }
  }

  if (argc - optind != 1) usage(argv[0]);

  string ref_fasta = argv[optind];
  string ref;
  size_t pos = ref_fasta.find_last_of(".");
  string output_name = ref_fasta.substr(0, pos) + ".mum";
  
  vector<string> refdescr; 
  vector<long> startpos;

  load_fasta(ref_fasta, ref, refdescr, startpos);

  // Automatically use 4 column format if there are multiple reference sequences.
  if(startpos.size() > 1) _4column = true;

  sa = new sparseSA(ref, refdescr, startpos, _4column, K);

  std::ofstream of(output_name.c_str(), std::ios::binary | std::ios::out);
  boost::archive::binary_oarchive oa(of);
  oa << sa;
  
  delete sa;
}


void usage(string prog) {
  cerr << "Usage: " << prog << " <reference-file>" << endl;
  cerr << "Additional options:" << endl;
  cerr << "-k             sampled suffix positions (one by default)" << endl;
  cerr << "-F             force 4 column output format regardless of the number of" << endl;
  cerr << "               reference sequence inputs"  << endl;
  cerr << "Example usage:" << endl;
  cerr << endl;
  cerr << "./create_mummer_index ref.fa" << endl;
  cerr << "Create an index file for ref.fa" << endl;
  
  exit(1);
}
