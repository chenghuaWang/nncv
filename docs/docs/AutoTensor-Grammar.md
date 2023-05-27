## 1. Types

| Type Name |   Size    |        Describe        |
| :-------: | :-------: | :--------------------: |
|   int16   | 16 Bytes  | The 16 bytes short int |
|  Tensor   | uncertain |   Tensor abstraction   |

```aten
import "std"

func main() -> int {
    int16 a = 20;

    Tensor foo<100, 100, 100, float32>;
    float32 d = 3.0;

    foo *= d;

    std.Print(foo);

    return 0;
}
```

## 2. Control Flow

### 2.1 If else

### 2.2 While do loop

## 3. Function

## 4. 'Class'

### 4.1 Struct

### 4.2 Impl

### 4.3 Constructor and De-constructor

## 5. Compile Flags

## 6. Memory model

## 7. Life Time

## 8. Import Libraries