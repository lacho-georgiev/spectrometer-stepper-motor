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

TreeNode item20 = { "Enter a0", NULL, 0, NULL };
TreeNode item21 = { "Enter a1", NULL, 0, NULL };
TreeNode item22 = { "Enter a2", NULL, 0, NULL };

TreeNode* menu1_children[] = { &item20, &item21, &item22 };

TreeNode menu1 = {"Calibration", NULL, sizeof(menu1_children)/sizeof(*menu1_children), menu1_children };

TreeNode item30 = { "speed", NULL, 0, NULL };
TreeNode item31 = { "reset motor pos", NULL, 0, NULL };
TreeNode item32 = { "steps per rev", NULL, 0, NULL };
TreeNode item33 = { "scan units", NULL, 0, NULL };

TreeNode* menu2_children[] = { &item30, &item31, &item32, &item33 };

TreeNode menu2 = {"Settings", NULL, sizeof(menu2_children)/sizeof(*menu2_children), menu2_children };

TreeNode* tree_children[] = { &menu0, &menu1, &menu2 };

TreeNode tree = { "root", NULL, sizeof(tree_children)/sizeof(*tree_children), tree_children };

void inject_parents(TreeNode* node) {
  for (int i = 0; i < (node->children_size); i++) {
    node->children[i]->parent = node;
    inject_parents(node->children[i]);
  }
  return;
}
