# The Package Reference Dialect

As we all know that, flat symbol in mlir will not rename when lowering and cross module symbol reference is quite complex. Therefor, a nested symbol reference dialect with package concept has its place.

Suppose the case below, it's really common in some high-level programming language(such as Python, Java) which has a module system.

```mlir
module @_main {
    module @_class_foo {
        func.func @nested_symbol() -> f32 {
            %1 = arith.constant 2.0 : f32
            return %1 : f32
        }
    }

    module @_class_bar {
        func.func @nested_symbol() -> f32 {
            %1 = arith.constant 12.0 : f32
            return %1 : f32
        }
    }

    func.func @_exec_main() -> () {
        %0 = func.call @_class_foo::@nested_symbol() : () -> f32
        %1 = func.call @_class_bar::@nested_symbol() : () -> f32
        return
    }
}
```

This case is incorrect in mlir. The symbol `@module_foo::@nested_symbol` will not rename and `func.func` do not support nested ref. 

TODO Add some illustrations

```mlir
package_ref.package @nn {attr } { // TODO design the attr

    package_ref.compose @_class { // TODO design the attr
        package_ref.func @do() -> () {

        }
    }

    package_ref.package @cv { // TODO design the attr
        package_ref.func @do() -> () { // TODO design the attr

        }
    }
}
```

It will lowering to: 

```mlir
module @nn {
    func.func @_nn__class_do() -> () {

    }

    func.func @_nn_cv_do() -> () {

    }
}
```

when calling it(module @nn) from other modules:

```mlir
package_ref.package @_main {

    // This scope is module system's responsible.
    package_ref.func @nn@_class@do() -> ()
    package_ref.func @nn@cv@do() -> ()
    
    package_ref.func @_exec_main() {
        %0 = package_ref.call @nn@cv@do() : ()
        %1 = package_ref.call @nn@_class@do() : ()
    }
}
```

lowering to:

```mlir
module @_main {

    // This scope is module system's responsible.
    func.func @_nn__class_do() -> ()
    func.func @_nn_cv_do() -> ()
    
    func.func @_exec_main() {
        %0 = func.call @_nn__class_do() : ()
        %1 = func.call @_nn_cv_do() : ()
    }
}
```

## Transforms

## Lowering