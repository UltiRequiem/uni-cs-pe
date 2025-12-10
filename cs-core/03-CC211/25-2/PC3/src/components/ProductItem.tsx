import type { Product } from "@/types/product";
import ProductActions from "./ProductActions";

export default function ProductItem({ product }: { product: Product }) {
  const total = product.price * product.quantity_sold;
  const available = product.quantity_max - product.quantity_sold;

  return (
    <tr
      key={product.id}
      className="hover:bg-gray-50 dark:hover:bg-gray-700/50 transition-colors"
    >
      <td className="px-6 py-4 text-sm font-medium text-gray-900 dark:text-white">
        {product.name}
      </td>
      <td className="px-6 py-4 text-sm text-gray-400 dark:text-gray-400 text-right">
        ${product.price.toFixed(2)}
      </td>
      <td className="px-6 py-4 text-sm text-gray-500 dark:text-gray-400 text-right">
        <div className="flex flex-col items-end">
          <span className="font-medium">
            {product.quantity_sold}/{product.quantity_max}
          </span>
          <span
            className={`text-xs ${
              available > 0
                ? "text-green-600 dark:text-green-400"
                : "text-red-600 dark:text-red-400"
            }`}
          >
            {available > 0 ? `${available} disponibles` : "Agotado"}
          </span>
        </div>
      </td>
      <td className="px-6 py-4">
        <ProductActions
          productId={product.id}
          currentSold={product.quantity_sold}
          maxQuantity={product.quantity_max}
        />
      </td>
      <td className="px-6 py-4 text-sm font-semibold text-gray-900 dark:text-white text-right">
        ${total.toFixed(2)}
      </td>
    </tr>
  );
}
