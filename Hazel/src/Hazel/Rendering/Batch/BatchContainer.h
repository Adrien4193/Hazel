#pragma once

namespace Hazel
{
	template<typename T>
	class BatchContainer
	{
	private:
		size_t size = 0;
		std::vector<T> data;

	public:
		inline BatchContainer(size_t max = 0)
			: data(max)
		{
		}

		constexpr size_t GetMaxSize() const
		{
			return data.size();
		}

		inline void SetMaxSize(size_t size)
		{
			data.resize(size);
		}

		constexpr size_t GetSize() const
		{
			return size;
		}

		inline const T *GetData() const
		{
			return data.data();
		}

		constexpr void Clear()
		{
			size = 0;
		}

		constexpr void Resize(size_t size)
		{
			this->size = size;
		}

		constexpr bool CanContain(size_t size) const
		{
			return this->size + size <= GetMaxSize();
		}

		inline T &Add(const T &item)
		{
			assert(size < data.size());
			return data[size++] = item;
		}
	};
}