/*
 * fwd_types.h — Forward declarations for types used across headers
 * before their defining header is included in FUNCTION.H's chain.
 */
#ifndef FWD_TYPES_H
#define FWD_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif
/* Needed by jshell.h before wwlib32.h is included */
int Get_Mouse_X(void);
int Get_Mouse_Y(void);
#ifdef __cplusplus
}
#endif

/*
** Minimal WWMouseClass definition so code that calls methods on
** the global WWMouse pointer can compile.  The real WIN32LIB mouse
** header pulls in the entire GBuffer chain; we just need stubs.
*/
#ifdef __cplusplus
class GraphicViewPortClass;   /* forward decl — enough for pointer args */
class GraphicBufferClass;

class WWMouseClass {
public:
    WWMouseClass(GraphicViewPortClass * /*scr*/, int /*w*/, int /*h*/) {}
    ~WWMouseClass() {}
    void *Set_Cursor(int /*xhotspot*/, int /*yhotspot*/, void * /*cursor*/) { return 0; }
    void Process_Mouse(void) {}
    void Hide_Mouse(void) {}
    void Show_Mouse(void) {}
    void Conditional_Hide_Mouse(int /*x1*/, int /*y1*/, int /*x2*/, int /*y2*/) {}
    void Conditional_Show_Mouse(void) {}
    int  Get_Mouse_State(void) { return 0; }
    int  Get_Mouse_X(void) { return 0; }
    int  Get_Mouse_Y(void) { return 0; }
    void Get_Mouse_XY(int &x, int &y) { x = 0; y = 0; }
    void Draw_Mouse(GraphicViewPortClass * /*scr*/) {}
    void Erase_Mouse(GraphicViewPortClass * /*scr*/, int /*forced*/ = 0) {}
    void Block_Mouse(GraphicBufferClass * /*buffer*/) {}
    void Unblock_Mouse(GraphicBufferClass * /*buffer*/) {}
    void Set_Cursor_Clip(void) {}
    void Clear_Cursor_Clip(void) {}
};
#endif

#endif /* FWD_TYPES_H */
