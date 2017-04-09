#include <iostream>
#include <sstream>
#include <string>

template <typename T>
class Chunk;

class Consumer
{
    template <typename T> friend class Chunk;
    class ChunkInner
    {
    public:
        ChunkInner(std::string p_data)
            : m_data{std::move(p_data)}
        {}

        const std::string& data()
        {
            return m_data;
        }


    private:
        std::string m_data;

    };

public:
    void accept_chunk(ChunkInner&& msg)
    {
        std::cout << "accepted chunk: " << msg.data() << '\n';
    }
};

template <typename T>
class Chunk
{
public:
    Chunk(std::string p_data, T p_extra_data)
        : valid{true}, data{std::move(p_data)}, extra_data{std::move(p_extra_data)}
    {
    }

    operator Consumer::ChunkInner ()
    {
        valid = false;
        extra_data = T{};
        return Consumer::ChunkInner(std::move(data));
    }

    std::string show()
    {
        if (valid)
        {
            std::stringstream strm{};
            strm << "data: " << data << " extra_data: " << extra_data << '\n';
            return strm.str();
        }
        else
        {
            return "message is invalid";
        }
        return data;
    }

private:
    bool valid;
    std::string data;
    T extra_data;

};

int main()
{
    auto chunk1 = Chunk<double>{"123 testing", 12.34};

    auto chunk2 = Chunk<char>{"345 testing", 'g'};

    std::cout << "before send: " << chunk1.show() << '\n';
    std::cout << "before send: " << chunk2.show() << '\n';

    auto comm_port = Consumer{};
    comm_port.accept_chunk(chunk1);
    std::cout << "after send: " << chunk1.show() << '\n';
    std::cout << "after send: " << chunk2.show() << '\n';
    comm_port.accept_chunk(chunk2);

    std::cout << "after send: " << chunk2.show() << '\n';



    return 0;
}
