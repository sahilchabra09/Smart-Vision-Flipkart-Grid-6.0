import { useState } from "react";
import { FaBars, FaTimes, FaUser, FaTachometerAlt } from "react-icons/fa";
import oats from "./assets/oats.webp";
import muscle from "./assets/protein.webp";
import honey from "./assets/honey.webp";
import honey2 from "./assets/honey2 dabur.webp";
import popcorn from "./assets/popcorn.webp";
import peanut from "./assets/peanut.webp";

const Dashboard = () => {
  const [sidebarOpen, setSidebarOpen] = useState(true);

  const products = [
    {
      img_url: oats,
      name: "DOCTOR'S CHOICE Protein Oats",
      brand: "DOCTOR'S CHOICE",
      quantity: 750,
      mrp: 589,
    },
    {
      img_url: muscle,
      name: "MUSCLEBLAZE High Protein Peanut Butter",
      brand: "MUSCLEBLAZE",
      quantity: 1000,
      mrp: 486,
    },
    {
      img_url: honey,
      name: "Tetley Lemon and Honey Green Tea Bags",
      brand: "Tetley",
      quantity: 100,
      mrp: 343,
    },
    {
      img_url: popcorn,
      name: "SHAH NANJI NAGSI SNN Popcorn Maize",
      brand: "SHAH NANJI NAGSI",
      quantity: 1000,
      mrp: 257,
    },
    {
      img_url: honey2,
      name: "Dabur Honey Squeezy",
      brand: "Dabur",
      quantity: 800,
      mrp: 279,
    },
    {
      img_url: peanut,
      name: "Pintola HIGH Protein Peanut Butter (Dark Chocolate)",
      brand: "Pintola",
      quantity: 1000,
      mrp: 524,
    },
  ];

  return (
    <div className="flex min-h-screen bg-gray-100">

      <aside
        className={`${
          sidebarOpen ? "w-64" : "w-0"
        } bg-blue-900 shadow-lg transition-all duration-300 overflow-hidden`}
      >
        <div className="h-16 flex items-center justify-between border-b p-4">
          
          <FaTimes
            onClick={() => setSidebarOpen(false)}
            className="cursor-pointer text-white"
          />
        </div>
        <nav className="p-4">
          <ul className="space-y-4 text-white">
            <li className="hover:text-yellow-300 cursor-pointer transition duration-200">Home</li>
            <li className="hover:text-yellow-300 cursor-pointer transition duration-200">Products</li>
            <li className="hover:text-yellow-300 cursor-pointer transition duration-200">Orders</li>
            <li className="hover:text-yellow-300 cursor-pointer transition duration-200">Customers</li>
          </ul>
        </nav>
      </aside>

      <div className="flex-1">
        <nav className="bg-blue-800 shadow-md p-4 flex justify-between items-center">
          <FaBars
            onClick={() => setSidebarOpen(true)}
            className="cursor-pointer text-white"
          />
          <div className="flex items-center space-x-2">
            <FaTachometerAlt className="h-6 w-6 text-white" />
            <h1 className="text-xl font-bold text-white">Dashboard</h1>
          </div>
          <div>
            <FaUser className="h-6 w-6 text-white" />
          </div>
        </nav>

        <div className="p-8">
          
          <div className="grid grid-cols-1 sm:grid-cols-2 lg:grid-cols-3 gap-8">
            {products.map((product, index) => (
              <div
                key={index}
                className="border p-6 rounded-lg shadow-lg hover:shadow-xl transition duration-300 bg-white transform hover:scale-105"
              >
                <img
                  src={product.img_url}
                  alt={product.name}
                  className="h-40 w-40 object-cover mx-auto mb-4 rounded-full border-2 border-gray-300"
                />
                <h2 className="text-lg font-semibold text-gray-800 text-center mb-2">
                  {product.name}
                </h2>
                <p className="text-center text-gray-500 mb-1">{product.brand}</p>
                <p className="text-center text-gray-600">
                  <span className="font-semibold">Quantity:</span> {product.quantity}g
                </p>
                <p className="text-center text-gray-700 mt-1 font-bold text-lg">
                  MRP: ₹{product.mrp}
                </p>
              </div>
            ))}
          </div>
        </div>
      </div>
    </div>
  );
};

export default Dashboard;
