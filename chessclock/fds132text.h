struct fdsChar {
byte character_map[7];
int width; //up to 8
};

struct fdsString {
fdsChar *value;
fdsString *rest;
};


