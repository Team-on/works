#define _VERSION_FRAMEWORK 1

#define _DELETE(p)				{ if(p){delete (p); (p)=nullptr;} }
#define _DELETE_ARRAY(p)		{ if(p){delete[] (p); (p)=nullptr;} }
#define _RELEASE(p)				{ if(p){(p)->Release(); (p)=nullptr;} }
#define _CLOSE(p)				{ if(p){(p)->Close(); delete (p); (p)=nullptr;} }

#define CASE					break; case