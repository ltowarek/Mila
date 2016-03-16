#ifndef MILA_BBP_SEQUENTIAL_H_
#define MILA_BBP_SEQUENTIAL_H_

namespace mila {
    namespace bbp {
        namespace sequential {
            class BBP {
            public:
                float Run();
                float Series(size_t j, size_t d);  // Compute sum_k 16^(d-k)/(8*k*j)
            };
        };  // sequential
    };  // bbp
}  // mila

#endif  // MILA_BBP_SEQUENTIAL_H_
