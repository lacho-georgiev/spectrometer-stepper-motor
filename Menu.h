struct TreeNode {
    const char* text;
    TreeNode* parent;
    int children_size;
    TreeNode** children;
};


TreeNode item10 = { "manual scan", NULL, 0, NULL };
TreeNode item11 = { "go_to", NULL, 0, NULL };

TreeNode* menu0_children[] = { &item10, &item11 };

TreeNode menu0 = { "Manual", NULL, sizeof(menu0_children)/sizeof(*menu0_children), menu0_children };

TreeNode item20 = { "auto scan", NULL, 0, NULL };
TreeNode item21 = { "range", NULL, 0, NULL };

TreeNode* menu1_children[] = { &item20, &item21 };

TreeNode menu1 = {"Auto", NULL, sizeof(menu1_children)/sizeof(*menu1_children), menu1_children };

TreeNode item30 = { "Enter a0", NULL, 0, NULL };
TreeNode item31 = { "Enter a1", NULL, 0, NULL };
TreeNode item32 = { "Enter a2", NULL, 0, NULL };

TreeNode* menu2_children[] = { &item30, &item31, &item32 };

TreeNode menu2 = {"Calibration", NULL, sizeof(menu2_children)/sizeof(*menu2_children), menu2_children };

TreeNode item40 = { "speed", NULL, 0, NULL };
TreeNode item41 = { "steps per rev", NULL, 0, NULL };

TreeNode* menu3_children[] = { &item40, &item41 };

TreeNode menu3 = {"Settings", NULL, sizeof(menu3_children)/sizeof(*menu3_children), menu3_children };

TreeNode* tree_children[] = { &menu0, &menu1, &menu2, &menu3 };

TreeNode tree = { "root", NULL, sizeof(tree_children)/sizeof(*tree_children), tree_children };

void inject_parents(TreeNode* node) {
  for (int i = 0; i < (node->children_size); i++) {
    node->children[i]->parent = node;
    inject_parents(node->children[i]);
  }
  return;
}
