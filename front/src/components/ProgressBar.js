export default function ProgressBar({ progress }) {
  return (
    <div className="w-full bg-yellow-900 rounded-full h-8">
      <div
        className="bg-red-900 h-8 rounded-full transition-width duration-300"
        style={{ width: `${progress}%` }}
      ></div>
    </div>
  );
}
