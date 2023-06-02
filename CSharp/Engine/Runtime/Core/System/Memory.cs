


namespace Engine
{
	using AlignType = System.UInt64;


	public class Memory
	{
		public const int AlignSize = sizeof(AlignType);


		public unsafe static void Clear(void* pointer, int byteCount)
		{
			int count	= byteCount / AlignSize;
			int mod		= byteCount % AlignSize;
			int offset	= byteCount - mod;

			for ( int index = 0; index < count; index++ )
				( (AlignType*)pointer )[index] = 0;

			for ( int index = 0; index < mod; index++ )
				( (byte*)pointer )[ offset + index ] = 0;
		}

		public unsafe static void Copy(void* from, void* to, int byteCount)
		{
			int count	= byteCount / AlignSize;
			int mod		= byteCount % AlignSize;
			int offset	= byteCount - mod;

			for ( int index = 0; index < count; index++ )
				( (AlignType*)to )[index] = ( (AlignType*)from )[index];

			for ( int index = 0; index < mod; index++ )
				( (byte*)to )[ offset + index ] = ( (byte*)from )[ offset + index ];
		}

		public unsafe static bool Equal(void* pointerA, void* pointerB, int byteCount)
		{
			int count	= byteCount / AlignSize;
			int mod		= byteCount % AlignSize;
			int offset	= byteCount - mod;

			for ( int index = 0; index < count; index++ )
				if (
					( (AlignType*)pointerA )[index] != ( (AlignType*)pointerB )[index]
					)
					return false;

			for ( int index = 0; index < mod; index++ )
				if (
					( (byte*)pointerA )[ offset + index ] != ( (byte*)pointerB )[ offset + index ]
					)
					return false;

			return true;
		}
	}
}