"use client";

import type { FormEvent } from "react";
import { useRef, useState } from "react";

interface ProductFormData {
  producto: string;
  precio: string;
  cantidad: string;
}

const ProductForm: React.FC = () => {
  const [formData, setFormData] = useState<ProductFormData>({
    producto: "",
    precio: "",
    cantidad: "",
  });

  const [errors, setErrors] = useState({
    producto: false,
    precio: false,
    cantidad: false,
  });

  const cantidadErrorRef = useRef<HTMLDivElement>(null);

  const handleInputChange = (e: React.ChangeEvent<HTMLInputElement>) => {
    const { name, value } = e.target;

    if (name === "cantidad") {
      const numericValue = value.replace(/[^0-9]/g, "");
      setFormData((prev) => ({ ...prev, [name]: numericValue }));

      if (cantidadErrorRef.current) {
        if (numericValue === "" || Number.isNaN(Number(numericValue))) {
          cantidadErrorRef.current.classList.remove("hidden");
        } else {
          cantidadErrorRef.current.classList.add("hidden");
        }
      }
    } else if (name === "precio") {
      const numericValue = value
        .replace(/[^0-9.]/g, "")
        .replace(/(\..*)\./g, "$1");
      setFormData((prev) => ({ ...prev, [name]: numericValue }));
    } else {
      setFormData((prev) => ({ ...prev, [name]: value }));
    }

    if (errors[name as keyof typeof errors]) {
      setErrors((prev) => ({ ...prev, [name]: false }));
    }
  };

  const handleSubmit = (e: FormEvent) => {
    e.preventDefault();

    const newErrors = {
      producto: formData.producto.trim() === "",
      precio:
        formData.precio === "" ||
        Number.isNaN(Number(formData.precio)) ||
        Number(formData.precio) < 0,
      cantidad:
        formData.cantidad === "" ||
        Number.isNaN(Number(formData.cantidad)) ||
        Number(formData.cantidad) < 0,
    };

    setErrors(newErrors);

    const isValid = !Object.values(newErrors).some((error) => error);

    if (isValid) {
      alert(
        `✅ Formulario enviado correctamente!\n\nProducto: ${formData.producto}\nPrecio: $${formData.precio}\nCantidad: ${formData.cantidad}`,
      );

      setFormData({
        producto: "",
        precio: "",
        cantidad: "",
      });

      if (cantidadErrorRef.current) {
        cantidadErrorRef.current.classList.add("hidden");
      }
    } else {
      alert("❌ Por favor, complete todos los campos correctamente.");
    }
  };

  const handleFocus = (fieldName: keyof typeof errors) => {
    setErrors((prev) => ({ ...prev, [fieldName]: false }));
  };

  return (
    <div className="bg-gray-900 min-h-screen py-8 px-4">
      <div className="max-w-md mx-auto bg-gray-800 rounded-2xl shadow-lg p-6 border border-gray-700">
        <h2 className="text-2xl font-bold text-white text-center mb-6">
          Datos del Producto
        </h2>

        <form id="productForm" className="space-y-4" onSubmit={handleSubmit}>
          {/* Campo Producto */}
          <div>
            <label
              htmlFor="producto"
              className="block text-sm font-medium text-gray-300 mb-2"
            >
              Producto:
            </label>
            <input
              type="text"
              id="producto"
              name="producto"
              value={formData.producto}
              onChange={handleInputChange}
              onFocus={() => handleFocus("producto")}
              required
              className={`w-full px-4 py-3 border rounded-lg focus:outline-none focus:ring-1 focus:ring-blue-500 focus:border-blue-500 transition-all duration-200 bg-gray-700 text-white placeholder-gray-400 ${
                errors.producto
                  ? "border-red-500 bg-red-900"
                  : "border-gray-600"
              }`}
              placeholder="Nombre del producto"
            />
          </div>

          {/* Campo Precio */}
          <div>
            <label
              htmlFor="precio"
              className="block text-sm font-medium text-gray-300 mb-2"
            >
              Precio:
            </label>
            <div className="relative">
              <div className="absolute inset-y-0 left-0 pl-3 flex items-center pointer-events-none">
                <span className="text-gray-400">$</span>
              </div>
              <input
                type="text"
                id="precio"
                name="precio"
                value={formData.precio}
                onChange={handleInputChange}
                onFocus={() => handleFocus("precio")}
                required
                className={`w-full pl-8 px-4 py-3 border rounded-lg focus:outline-none focus:ring-1 focus:ring-blue-500 focus:border-blue-500 transition-all duration-200 bg-gray-700 text-white placeholder-gray-400 ${
                  errors.precio
                    ? "border-red-500 bg-red-900"
                    : "border-gray-600"
                }`}
                placeholder="0.00"
              />
            </div>
          </div>

          {/* Campo Cantidad */}
          <div>
            <label
              htmlFor="cantidad"
              className="block text-sm font-medium text-gray-300 mb-2"
            >
              Cantidad:
            </label>
            <input
              type="text"
              id="cantidad"
              name="cantidad"
              value={formData.cantidad}
              onChange={handleInputChange}
              onFocus={() => handleFocus("cantidad")}
              required
              className={`w-full px-4 py-3 border rounded-lg focus:outline-none focus:ring-1 focus:ring-blue-500 focus:border-blue-500 transition-all duration-200 bg-gray-700 text-white placeholder-gray-400 ${
                errors.cantidad
                  ? "border-red-500 bg-red-900"
                  : "border-gray-600"
              }`}
              placeholder="Solo números enteros"
            />
            <div
              ref={cantidadErrorRef}
              className="hidden text-red-400 text-xs mt-1 ml-1"
            >
              Por favor, ingrese solo números enteros
            </div>
          </div>

          {/* Botón Centrado */}
          <div className="flex justify-center pt-4">
            <button
              type="submit"
              className="bg-green-500 hover:bg-green-600 text-white font-semibold py-3 px-8 rounded-lg transition-all duration-200 transform hover:scale-105 focus:outline-none focus:ring-2 focus:ring-green-500 focus:ring-opacity-50"
            >
              GUARDAR
            </button>
          </div>
        </form>
      </div>
    </div>
  );
};

export default ProductForm;
