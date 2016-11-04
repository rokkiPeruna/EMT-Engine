#ifndef JEJ_GRAPHICS_HPP
#define JEJ_GRAPHICS_HPP



namespace jej
{
	class Graphics

	{
	public:

		enum class DEFAULTS
		{
			POSITIONS,
			INDICIES,
			TEXTURE_COORDINATES
		};


		//Short: abstract base class for OpenGL Graphics.
		Graphics();

		virtual ~Graphics();

	protected:

		virtual void _swapBuffers() = 0;

	};

}
#endif // End of namespace