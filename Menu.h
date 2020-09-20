struct TreeNode {
    const char* text;
    TreeNode* parent;
    int children_size;
    TreeNode** children;
};


TreeNode item_manual_scan = {"Manual scan", NULL, 0, NULL };
TreeNode item_go_to = {"Go to", NULL, 0, NULL };

//TreeNode* menu0_children[] = {&menu0, &item11 };

//TreeNode menu0 = { "Manual", NULL, sizeof(menu0_children)/sizeof(*menu0_children), menu0_children };

TreeNode item_a0 = {"Enter a0", NULL, 0, NULL };
TreeNode item_a1 = {"Enter a1", NULL, 0, NULL };
TreeNode item_a2 = {"Enter a2", NULL, 0, NULL };

TreeNode* menu_calibration_children[] = {&item_a0, &item_a1, &item_a2 };

TreeNode menu_calibration = {"Calibration", NULL, sizeof(menu_calibration_children) / sizeof(*menu_calibration_children), menu_calibration_children };

TreeNode item_scan_units = {"scan units", NULL, 0, NULL };
TreeNode item_set_wavelength = {"set wavelength", NULL, 0, NULL };
TreeNode item_intervals = {"intervals", NULL, 0, NULL };
TreeNode item_set_motor_pos = {"set motor pos", NULL, 0, NULL };
TreeNode item_SPR = {"steps per rev", NULL, 0, NULL };
TreeNode item_speed = {"speed", NULL, 0, NULL };

TreeNode* menu_settings_children[] = { &item_scan_units,  &item_set_wavelength, &item_intervals, &item_set_motor_pos, &item_speed, &item_SPR };

TreeNode menu_settings = {"Settings", NULL, sizeof(menu_settings_children) / sizeof(*menu_settings_children), menu_settings_children };

TreeNode* root_children[] = {&item_manual_scan, &item_go_to, &menu_settings, &menu_calibration };

TreeNode root = {"root", NULL, sizeof(root_children) / sizeof(*root_children), root_children };

void inject_parents(TreeNode* node) {
  for (int i = 0; i < (node->children_size); i++) {
    node->children[i]->parent = node;
    inject_parents(node->children[i]);
  }
  return;
}
