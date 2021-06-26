#ifndef TEXT_H
#define TEXT_H

#include <raylib.h>
#include <string>

class Text
{
	private:
    std::string text;
    int x;
    int initX;
    int initY;
    int y;
    Color color;
    int size;

    bool scaling;
    double startScale;
    void calcPos(int x, int y);
	public:

		Text();
		~Text();

    void setText(const std::string & str, int x, int y, int size, Color color);
    void setText(const char * str, int x, int y, int size, Color color);
    void setText(const std::string & str);
    void setText(const char * str);

    void updatePos(int x, int y);
    void setColor(Color color);
    void setSize(int size);

    void render();

    /**
     * @brief Scale text linearly over a duration
     *
     * @param duration
     * @param startSize
     * @param endSize
     * @return true Done scaling
     * @return false Busy scaling
     */
    bool scale(float duration, int startSize, int endSize);

};
#endif
