/**
 * File              : entities.h
 * Author            : Igor V. Sementsov <ig.kuzm@gmail.com>
 * Date              : 02.12.2022
 * Last Modified Date: 02.12.2022
 * Last Modified By  : Igor V. Sementsov <ig.kuzm@gmail.com>
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>


#define CONFIG_FILE "gnertrain.ini"

struct entity {
	char name[32];   // name of entity
	char colo[32];   // color
	char desc[256];  // description
};

char *colors[] = {
	"a0",                  // no color
	"aliceblue",
	"antiquewhite",
	/*"aqua",*/
	/*"aquamarine",*/
	/*"azure",*/
	/*"beige",*/
	/*"bisque",*/
	/*"black",*/
	/*"blanchedalmond",*/
	"blue",
	/*"blueviolet",*/
	"brown",
	/*"burlywood",*/
	/*"cadetblue",*/
	/*"chartreuse",*/
	"chocolate",
	"coral",
	/*"cornflowerblue",*/
	/*"cornsilk",*/
	/*"crimson",*/
	"cyan",
	"darkblue",
	"darkcyan",
	/*"darkgoldenrod",*/
	"darkgray",
	"darkgreen",
	/*"darkgrey",*/
	/*"darkkhaki",*/
	/*"darkmagenta",*/
	/*"darkolivegreen",*/
	"darkorange",
	/*"darkorchid",*/
	"darkred",
	/*"darksalmon",*/
	/*"darkseagreen",*/
	/*"darkslateblue",*/
	/*"darkslategray",*/
	/*"darkturquoise",*/
	"darkviolet",
	/*"deeppink",*/
	/*"deepskyblue",*/
	/*"dimgray",*/
	/*"dodgerblue",*/
	/*"firebrick",*/
	/*"floralwhite",*/
	/*"forestgreen",*/
	/*"fuchsia",*/
	/*"gainsboro",*/
	/*"ghostwhite",*/
	"gold",
	/*"goldenrod",*/
	"gray",
	"green",
	"greenyellow",
	/*"honeydew",*/
	/*"hotpink",*/
	/*"indianred",*/
	"indigo",
	/*"ivory",*/
	/*"khaki",*/
	/*"lavender",*/
	/*"lavenderblush",*/
	/*"lawngreen",*/
	/*"lemonchiffon",*/
	"lightblue",
	"lightcoral",
	"lightcyan",
	"lightgoldenrodyellow",
	"lightgray",
	"lightgreen",
	"lightgrey",
	"lightpink",
	"lightsalmon",
	"lightseagreen",
	"lightskyblue",
	"lightslategray",
	"lightsteelblue",
	"lightyellow",
	"lime",
	"limegreen",
	"linen",
	"magenta",
	"maroon",
	"mediumaquamarine",
	"mediumblue",
	"mediumorchid",
	"mediumpurple",
	"mediumseagreen",
	"mediumslateblue",
	"mediumspringgreen",
	"mediumturquoise",
	"mediumvioletred",
	"midnightblue",
	"mintcream",
	"mistyrose",
	"moccasin",
	"navajowhite",
	"navy",
	"oldlace",
	"olive",
	"olivedrab",
	"orange",
	"orangered",
	"orchid",
	"palegoldenrod",
	"palegreen",
	"paleturquoise",
	"palevioletred",
	"papayawhip",
	"peachpuff",
	"peru",
	"pink",
	"plum",
	"powderblue",
	"purple",
	"rebeccapurple",
	"red",
	"rosybrown",
	"royalblue",
	"saddlebrown",
	"salmon",
	"sandybrown",
	"seagreen",
	"seashell",
	"sienna",
	"silver",
	"skyblue",
	"slateblue",
	"slategray",
	"slategrey",
	"snow",
	"springgreen",
	"steelblue",
	"tan",
	"teal",
	"thistle",
	"tomato",
	"turquoise",
	"violet",
	"wheat",
	"white",
	"whitesmoke",
	"yellow",
	"yellowgreen",
};

struct entity **entities_init(){
	struct entity **e = malloc(8 * 100);
	if (!e)
		return NULL;

	int i = 0;
	struct entity *none = malloc(sizeof(struct entity));
	if (!none)
		return NULL;
	strcpy(none->name, "NONE");
	strcpy(none->colo, colors[i]);
	strcpy(none->desc, "No entity");

	e[i++] = none;

	//load file
	GKeyFile *key_file = g_key_file_new ();
	if (g_key_file_load_from_file(key_file, CONFIG_FILE, 0, NULL)){
		//get keys
		gsize len;
		GError *err = NULL;
		gchar ** entities = 
				g_key_file_get_keys(key_file, "entities", &len, &err);	

		if (err)
			perror(err->message);

		for (i = 1; i < len + 1; ++i) {
			e[i] = malloc(sizeof(struct entity));
			if (!none)
				break;
			
			strncpy(e[i]->name, entities[i-1], 31);
			e[i]->name[31] = 0;
			strcpy(e[i]->colo, colors[i]);

			//description
			err = NULL;
			gchar *desc = 
					g_key_file_get_string(key_file, "entities", entities[i-1], &err);
			if (err)
				perror(err->message);
			
			strncpy(e[i]->desc, desc, 127);
			e[i]->desc[127] = 0;		
		}
	}

	g_key_file_free(key_file);
	e[i++] = NULL;
	return e;
};

struct entity *entity_with_colo(struct entity **entities, const char *colo){
	printf("GET COLOR\n");
	int i = 0;
	for (i=0; entities[i]; ++i){
		if (strncmp(entities[i]->colo, colo, 31) == 0)
			return entities[i];
	}
	return NULL;
};
