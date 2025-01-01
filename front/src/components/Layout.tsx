import Head from "next/head";
import Link from "next/link";
import { ReactNode } from "react";

interface LayoutProps {
  children: ReactNode;
  title: string;
  description: string;
}

const Layout = ({ children, title, description }: LayoutProps): JSX.Element => {
  return (
    <>
      <Head>
        <title>{title}</title>
        <meta name="description" content={description} />
        {/* Meta tags para SEO */}
        <meta name="viewport" content="width=device-width, initial-scale=1" />
        <meta name="keywords" content="Next.js, Tutorial, Docker, TypeScript" />
      </Head>
      <nav className="bg-gradient-to-r from-blue-500 to-purple-600 p-4">
        <ul className="flex flex-wrap gap-y-2 md:gap-y-0 md:gap-x-6 justify-center md:justify-start">
          <li className="mx-2">
            <Link
              href="/"
              className="block text-white font-semibold hover:text-gray-200"
            >
              Início
            </Link>
          </li>
          <li className="mx-2">
            <Link
              href="/motoboys"
              className="block text-white font-semibold hover:text-gray-200"
            >
              Motoboys
            </Link>
          </li>
        </ul>
      </nav>
      <main className="px-4 sm:px-6 lg:px-8 py-6">{children}</main>
    </>
  );
};

export default Layout;
