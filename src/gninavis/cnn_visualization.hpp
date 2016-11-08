#include <openbabel/mol.h>
#include <set>
#include <unordered_set>
#include "cnn_scorer.h"
#include "molgetter.h"

struct vis_options
{
  std::string ligand_name;
  std::string receptor_name;
  std::string receptor_output;
  std::string ligand_output;

  bool frags_only;
  bool atoms_only;
  bool verbose;
  bool output_files;

  float box_size;

  //vis_options(): box_size(23.5), frags_only(false), atoms_only(false), verbose(false) {}
};

class cnn_visualization
{
    public:
    cnn_visualization(const vis_options &visopts, const cnn_options &cnnopts, const vec &center);
    void color();
    void print();

    private:
    std::string rec_string, lig_string, rec_pdb_string, lig_pdb_string; 
    OpenBabel::OBMol lig_mol, rec_mol;
    float size, original_score;
    float cenCoords [3];
    vis_options visopts;
    cnn_options cnnopts;
    const vec* center;
    model unmodified_receptor;
    model unmodified_ligand;
    bool frags_only, atoms_only,  verbose;

    void process_molecules();
    std::string modify_pdbqt(std::vector<int> atoms_to_remove, bool isRec);
    float score_modified_receptor(const std::string &modified_rec_string);
    float score_modified_ligand(const std::string &modified_lig_string);

    std::vector<std::string> rec_map;
    std::vector<std::string> lig_map;
    float score(const std::string &molString, bool isRec);
    void write_scores(std::vector<float> scoreList, bool isRec);
    bool check_in_range(std::unordered_set<int> atomList);
    float transform_score(float score_val);
    void remove_residues();
    void remove_each_atom();
    void output_modified_string(const std::string &modified_string, const std::vector<int> &atoms_removed,
                                  bool receptor);

};
